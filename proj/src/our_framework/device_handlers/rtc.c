#include "rtc.h"

int rtc_output(uint8_t command, uint8_t *output) {
    if (sys_outb(0x70, command) != 0) return 1;
    if (util_sys_inb(0x71, output) != 0) return 1;
    return 0;
}

int rtc_is_updating() {
    uint8_t result;
    if (rtc_output(10, &result)) return 1;
	return result & BIT(7);
}

int rtc_update_time(uint8_t *hours) {
    
    // Se o RTC estiver ocupado a atualizar os contadores não devemos ler dados
    if (rtc_is_updating() != 0) return 1;

    // Leitura das horas -> comando 4
    if (rtc_output(4, hours) != 0) return 1;
    return 0;
}
