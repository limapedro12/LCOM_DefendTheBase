#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>

int rtc_input(uint8_t cmd, uint *place_to_store);
int rtc_output(uint8_t cmd, uint8_t output);
int is_rtc_updating();
int rtc_update_time(uint *hours, uint *minutes);

#endif
