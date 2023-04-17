#ifndef KBC_H
#define KBC_H

#include <lcom/lcf.h>
#include "i8042.h"
#include "utils.h"

#define KBD_KEY 30
#define IRQ_SET_KBD BIT(KBD_KEY)

int keyboard_subscribe_interrupt();
int keyboard_unsubscribe_interrupt();
u8_t read_scancode();

#endif
