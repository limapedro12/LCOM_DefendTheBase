#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include "i8042.h"

#define MOUSE_KEY 29
#define IRQ_SET_MOUSE BIT(MOUSE_KEY)

int mouse_subscribe_interrupt();
int mouse_unsubscribe_interrupt();
int parse_to_packet(u8_t byte[3], struct packet* pp);

#endif
