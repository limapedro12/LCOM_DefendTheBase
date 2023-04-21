#include "game.h"
#include "our_framework/framework_essencials.h"

int time_0;

int before(){
  turn_on_graphics();
  time_0 = get_time_counter();
  printf("Hello World from inside Game!\n");
  return 0;
}

int x = 20;
int y = 20;

void game(){
  if(is_key_pressed_code(0x81)){
    printf("Esc Key pressed outside!\n");
    quit();
  }
  if(is_key_pressed(' ', false)){
    printf("Space Key pressed outside!\n");
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

  // printf("MOuse position: (%d, %d)\n", get_mouse_position().x, get_mouse_position().y);

  if(is_time_interval_elapsed_seconds(time_0, 5)){
    printf("5 seconds has passed!");
    quit();
  }

  draw_rectangle(x, y, 2, 2, 0x00FF00);
  draw_rectangle(780 + get_mouse_position().x, 680 + get_mouse_position().y, 2, 2, 0xFF0000);
}

int after(){
    return 0;
}
