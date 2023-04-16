#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>
#include "i8254.h"

#define TIMER_KEY 31
#define IRQ_SET_TIMER BIT(TIMER_KEY)

int timer_subscribe_interrupt();
int timer_unsubscribe_interrupt();
bool is_timer_0_interrupt(int ipc_status, message msg);

#endif
