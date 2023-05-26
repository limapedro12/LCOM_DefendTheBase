#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include "our_framework/framework_essencials.h"
#include "bullet.h"
#include "xpm/tower_orange/tower_orange.h"
#include "xpm/tower_purple/tower_purple.h"
#include "xpm/background_without_towers.xpm"

xpm_image_t background_img;
uint8_t * background_pixmap;

void load_xpms();

void draw_map(char map[12][16]);

void draw_lives(int lives);

void draw_tower(int tower_id, int tower_x, int tower_y);

#endif
