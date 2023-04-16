#ifndef TIMER_H
#define TIMER_H

#include <lcom\lcf.h>
#include "i8254.h"

int timer_subscribe_int(u8_t key);
int timer_unsubscribe_int();
bool is_timer_0_interrupt();

#endif
