#include "rtc.h"

int rtc_input(uint8_t cmd, uint *place_to_store) {
  if(sys_outb(0x70, cmd) != 0)
    return 1;
  if(sys_inb(0x71, place_to_store) != 0)
    return 1;
  return 0;
}

int rtc_output(uint8_t cmd, uint8_t output) {
  if(sys_outb(0x70, cmd) != 0)
    return 1;
  if(sys_outb(0x71, output) != 0)
    return 1;
  return 0;
}

int rtc_is_updating() {
  uint result;
  if (rtc_input(10, &result)) return 1;
	return result & BIT(7);
}

int is_rtc_updating() {
  uint ret;
  if(rtc_input(10, &ret)) return 1;
	return ret & BIT(7);
}


int rtc_update_time(uint *hours, uint *minutes) {
    if (rtc_is_updating() != 0){
      printf("RTC is updating\n");	
      return 1;
    }
    if (rtc_input(4, hours) != 0){
      printf("Error reading hours\n");
      return 1;
    }
    if (rtc_input(2, minutes) != 0){
      printf("Error reading minutes\n");
      return 1;
    }
    *hours -= 6; *hours %= 24;
    // *minutes -= 6; *minutes %= 60;
    return 0;
}
