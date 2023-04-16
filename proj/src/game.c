#include "game.h"
#include "our_framework/framework_essencials.h"

int time_0;

int before(){
  time_0 = get_time_counter();
  printf("Hello World from inside Game!\n");
  return 0;
}

void game(){
    if(is_time_interval_elapsed_milliseconds(time_0, 200)){
      printf("2 millisecond has passed!");
      time_0 = get_time_counter();
      quit();
    }
}

int after(){
    return 0;
}
