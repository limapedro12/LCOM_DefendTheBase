#include "timer.h"

int hook_id = 0;

int timer_subscribe_int(u8_t key){
    hook_id = key;
    if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)){
        printf("Error setting policy\n");
        return 1;
    }
    return 0;
}

int timer_unsubscribe_int();
bool is_timer_0_interrupt();
