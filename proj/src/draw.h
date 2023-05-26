#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include "our_framework/framework_essencials.h"
#include "bullet.h"
#include "xpm/tower_orange/tower_orange.h"
#include "xpm/tower_purple/tower_purple.h"
#include "xpm/background_without_towers.xpm"
#include "xpm/menu.xpm"
#include "xpm/start_game.xpm"
#include "xpm/quit.xpm"
#include "xpm/start_game_glow.xpm"
#include "xpm/quit_glow.xpm"

xpm_image_t background_img;
uint8_t * background_pixmap;

xpm_image_t menu_img;
uint8_t * menu_pixmap;

xpm_image_t start_game_img;
uint8_t * start_game_pixmap;

xpm_image_t quit_img;
uint8_t * quit_pixmap;

xpm_image_t start_game_glow_img;
uint8_t * start_game_glow_pixmap;

xpm_image_t quit_glow_img;
uint8_t * quit_glow_pixmap;

int last_position[6];

void load_xpms();

void draw_map(char map[12][16]);

void draw_lives(int lives);

void draw_tower(int tower_id, int tower_x, int tower_y);

#endif
