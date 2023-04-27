#include "game.h"
#include "our_framework/framework_essencials.h"

int time_0;

int before(){
  turn_on_graphics();
  time_0 = get_time_counter();
  // printf("Hello World from inside Game!\n");
  return 0;
}

int x = 20;
int y = 20;

void game(){
  clear_screen();
  if(is_key_pressed_code(0x81)){
    // printf("Esc Key pressed outside!\n");
    quit();
  }
  if(is_key_pressed(' ', false)){
    // printf("Space Key pressed outside!\n");
    quit();
  }

  if(is_key_pressed('a', false)){
    x--;
  }
  if(is_key_pressed('d', false)){
    x++;
  }
  if(is_key_pressed('w', false)){
    y--;
  }
  if(is_key_pressed('s', false)){
    y++;
  }

  // printf("Mouse position: (%d, %d)\n", get_mouse_position().x, get_mouse_position().y);

  // if(is_time_interval_elapsed_seconds(time_0, 5)){
  //   printf("5 seconds has passed!");
  //   quit();
  // }

  draw_rectangle(x, y, 30, 30, 0x00FF00);
  if(get_mouse_position().x < 300 && get_mouse_position().x > -300 && get_mouse_position().y < 200 && get_mouse_position().y > -200)
    draw_rectangle(400 + get_mouse_position().x, 300 - get_mouse_position().y, 30, 30, 0xFF0000);
  // if(get_mouse_position().x > 0 && get_mouse_position().y > 0)
  //   draw_rectangle(300, 300, 30, 30, 0xFF0000);
  // else if(get_mouse_position().x > 0 && get_mouse_position().y < 0)
  //   draw_rectangle(300, -300, 30, 30, 0x00FF00);
  // else if(get_mouse_position().x < 0 && get_mouse_position().y > 0)
  //   draw_rectangle(-300, 300, 30, 30, 0x0000FF);
  // else if(get_mouse_position().x < 0 && get_mouse_position().y < 0)
  //   draw_rectangle(-300, -300, 30, 30, 0xFFFFFF);
}

int after(){
    return 0;
}
