#include "../framework_essencials.h"

bool game_running = true;
u8_t code = 0;

unsigned long long time_counter = 0;

bool graphics_on = false;

char* video_mem = NULL;

int run(void (*func)()){
  if(graphics_on)
    video_mem = vg_init(0x115);

  timer_subscribe_interrupt();
  keyboard_subscribe_interrupt();
  
  int ipc_status;
  message msg;
  int r = 0;
  while(game_running){
    r = driver_receive(ANY, &msg, &ipc_status);
    if(r != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if ((is_ipc_notify(ipc_status) && 
     (_ENDPOINT_P(msg.m_source) == HARDWARE))){
      if (msg.m_notify.interrupts & IRQ_SET_KBD){
        code = read_scancode();
        // printf("Code: 0x%x\n", code);
      }
    }

    if(is_timer_0_interrupt(ipc_status, msg)){
      func();
      time_counter++;
    }
  }

  keyboard_unsubscribe_interrupt();
  timer_unsubscribe_interrupt();

  if(graphics_on)
    vg_exit();

  return 0;
}

void quit(){
  game_running = false;
  return;
}

int get_time_counter(){
    return time_counter % 600000000;
}

bool is_time_interval_elapsed_seconds(int start_time, int interval){
  if(interval * 60 > 600000000){
    printf("Interval too big, max interval is 10000000 seconds\n");
    return false;
  }
  if(600000000-start_time < interval)
    start_time = -start_time;
  return ((int)((time_counter%600000000) / 60) >= start_time + interval);
}

bool is_time_interval_elapsed_milliseconds(int start_time, int interval){
  interval = (interval * 60)/1000;
  if(interval > 600000000){
    printf("Interval too big, max interval is 10000000000 milliseconds\n");
    return false;
  }
  if(600000000-start_time < interval)
    start_time = -start_time;
  return ((int)(time_counter%600000000) >= start_time + interval);
}

bool is_key_pressed_code(uint8_t scancode){
  return code == scancode;
}

bool is_key_pressed(char key){
  return code == char_to_scancode(key);
}

void turn_on_graphics(){
  if(!graphics_on){
    vg_init(0x105);
    graphics_on = true;
  }
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color){
  if(!graphics_on){
    printf("Graphics not on!\n");
    return;
  }
  draw_rect(x, y, width, height, color, video_mem, 0x115);
}
