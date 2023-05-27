#ifndef NIGHT_MODE_H
#define NIGHT_MODE_H

#include <lcom/lcf.h>
#include "our_framework/framework_essencials.h"

bool* night_mode_filter;

void start_night_mode();

double get_value_to_multiply();

void apply_night_mode_on_xpm(uint8_t* pixmap, xpm_image_t img);

void highlight_map(int x, int y, int range, uint8_t* pixmap, xpm_image_t img);

#endif
