#include "../framework_essencials.h"

bool game_running = true;

int ipc_status;
message msg;
int r;

int run(void (*func)()){
  timer_subscribe_interrupt();

  unsigned long long time_counter = 0;
  
  while(game_running){
    r = driver_receive(ANY, &msg, &ipc_status);
    if(r != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if(is_timer_0_interrupt(ipc_status, msg)){
      func();
      time_counter++;
    }
  }

  timer_unsubscribe_interrupt();

  return 0;
}

void quit(){
    game_running = false;
    return;
}
