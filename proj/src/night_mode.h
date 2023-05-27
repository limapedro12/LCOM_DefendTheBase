#ifndef NIGHT_MODE_H
#define NIGHT_MODE_H

#include <lcom/lcf.h>
#include "our_framework/framework_essencials.h"

bool* night_mode_filter;

void start_night_mode();

void highlight_xpm_loaded(uint16_t x, uint16_t y, uint8_t* xpm, xpm_image_t img, uint color_to_ignore);

void remove_hightlight();

void apply_night_mode();

double get_value_to_multiply();

void apply_night_mode_on_xpm(uint8_t* pixmap, xpm_image_t img);

void highlight_map(int x, int y, int range, uint8_t* pixmap, xpm_image_t img);

#endif
