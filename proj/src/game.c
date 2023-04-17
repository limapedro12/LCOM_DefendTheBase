#include "game.h"
#include "our_framework/framework_essencials.h"

int time_0;

int before(){
  time_0 = get_time_counter();
  printf("Hello World from inside Game!\n");
  return 0;
}

void game(){
    if(is_key_pressed(0x81)){
      printf("Esc Key pressed outside!\n");
      quit();
    }
    if(is_time_interval_elapsed_seconds(time_0, 5)){
      printf("5 seconds has passed!");
      quit();
    }
}

int after(){
    return 0;
}
