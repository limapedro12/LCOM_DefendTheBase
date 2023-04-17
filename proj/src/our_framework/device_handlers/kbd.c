#include "kbd.h"

int hook_id_keyboard = 0;

int keyboard_subscribe_interrupt(){
  hook_id_keyboard = KBD_KEY;
  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_keyboard)){
    printf("Error while subscribing to keyboard's interrupts\n");
    return 1;
  }
  return 0;
}

int keyboard_unsubscribe_interrupt(){
  if(sys_irqrmpolicy(&hook_id_keyboard)){
    printf("Error while unsubscribing to keyboard's interrupts\n");
    return 1;
  }
  return 0;
}

u8_t read_scancode(){
  u8_t data;
  uint stat;

  while(1) {
    sys_inb(KBC_ST_REG, &stat); 
    if( stat & KBC_OBF ) {
      util_sys_inb(KBC_OUT_BUF, &data);
      if ( (stat &(KBC_PAR_ERR | KBC_TO_ERR)) == 0 )
        return data;
      else
        return -1;
      }
    tickdelay(2000);
  }
}
