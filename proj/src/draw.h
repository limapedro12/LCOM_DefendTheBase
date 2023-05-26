#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include "our_framework/framework_essencials.h"
#include "bullet.h"
#include "xpm/tower_orange/tower_orange.h"
#include "xpm/tower_purple/tower_purple.h"
#include "xpm/background_without_towers.xpm"
#include "xpm/menu.xpm"

xpm_image_t background_img;
uint8_t * background_pixmap;

xpm_image_t menu_img;
uint8_t * menu_pixmap;

/**
 * @brief loads xpms
 * 
 */
void load_xpms();

/**
 * @brief function that draws the map
 * 
 * @param map nested array that contains the map
 */
void draw_map(char map[12][16]);

/**
 * @brief function that draws the lives
 * 
 * @param lives number of lives
 */
void draw_lives(int lives);

/**
 * @brief function that draws towers
 * 
 * @param tower_id tower id
 * @param tower_x tower x position
 * @param tower_y tower y position
 */
void draw_tower(int tower_id, int tower_x, int tower_y);

#endif
