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
int enemy_x = 0;
int enemy_y = 300;

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
    x-=6;
  }
  if(is_key_pressed('d', false)){
    x+=6;
  }
  if(is_key_pressed('w', false)){
    y-=3;
  }
  if(is_key_pressed('s', false)){
    y+=3;
  }

  if (x > 800-30)
    x = 800-30; 
  if (x < 0)
    x = 0;
  if (y > 600-30)
    y = 600-30;
  if (y < 0)
    y = 0;
  enemy_x+= 12;
  if(enemy_x > 800)
    enemy_x = 0;
  

  // printf("Mouse position: (%d, %d)\n", get_mouse_position().x, get_mouse_position().y);

  // if(is_time_interval_elapsed_seconds(time_0, 5)){
  //   printf("5 seconds has passed!");
  //   quit();
  // }

  draw_rectangle(x, y, 30, 30, 0x00FF00);
  draw_rectangle(400 + get_mouse_position().x, 300 - get_mouse_position().y, 30, 30, 0xFF0000);
  draw_rectangle(enemy_x, enemy_y, 30, 30, 0x0000FF);
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
