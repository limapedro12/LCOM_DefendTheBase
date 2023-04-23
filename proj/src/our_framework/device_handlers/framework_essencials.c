#include "../framework_essencials.h"

bool game_running = true;
u8_t code = 0;
u8_t mouse_arr[3] = {0, 0, 0};
struct packet pp;
int current = 0;

position mouse_position = {0, 0};

unsigned long long time_counter = 0;

bool graphics_on = false;

char* video_mem = NULL;

int run(void (*func)()){

  timer_subscribe_interrupt();
  keyboard_subscribe_interrupt();
  mouse_subscribe_interrupt();
  
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
        read_scancode(&code);
        // printf("Code: 0x%x\n", code);
      }
      if (msg.m_notify.interrupts & IRQ_SET_MOUSE){
        read_scancode(&(mouse_arr[current]));
        if(current == 2){
          parse_to_packet(mouse_arr, &pp);
          mouse_position.x += pp.delta_x;
          mouse_position.y += pp.delta_y;
          // printf("Mouse position: (%d, %d)\n", mouse_position.x, mouse_position.y);
        }
        current = (current + 1) % 3;
      }
    }
    // printf("Time counter: %d\n", time_counter);

    if(is_timer_0_interrupt(ipc_status, msg)){
      func();
      time_counter++;
    }
  }

  mouse_unsubscribe_interrupt();
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

bool is_key_pressed(char key, bool isBreak){
  if(isBreak){
    if(code == (char_to_scancode(key) | BIT(7))){
      // printf("Got break code: 0x%x", code);
      code = 0;
      return true;
    }
    return false;
  }

  return code == char_to_scancode(key);
}

position get_mouse_position(){
  return mouse_position;
}

void turn_on_graphics(){
  if(!graphics_on){
    graphics_on = true;
    video_mem = vg_init(0x115);
  }
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color){
  if(!graphics_on){
    printf("Graphics not on!\n");
    return;
  }
  draw_rect(x, y, width, height, color, video_mem, 0x115);
}

void clear_screen(){
  if(!graphics_on){
    printf("Graphics not on!\n");
    return;
  }
  draw_rect(0, 0, get_width(0x115), get_height(0x115), 0, video_mem, 0x115);
}
