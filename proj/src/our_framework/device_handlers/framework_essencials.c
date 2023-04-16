#include "../framework_essencials.h"

bool game_running = true;

int run(void (*func)()){

  while(game_running){
        func();
    // printf("In while, counter: %d\n", counter);
    // printf("In while, safe_counter: %d\n", safe_counter);
    //safe_counter++;
    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status) && 
       (_ENDPOINT_P(msg.m_source) == HARDWARE)) /* receive notification */
        if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
          /* process it */
          timer_int_handler();
          // printf("counter: %d\n", counter);
          // printf("counter: %d\n", counter);
          if(counter % 60 == 0){
            timer_print_elapsed_time();
          }
        }
  }


    return 0;
}

void quit(){
    game_running = false;
    return;
}
