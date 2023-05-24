#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>

int rtc_output(uint8_t command, uint8_t *output);
int rtc_is_updating();
int rtc_update_time(uint8_t *hours);

#endif
