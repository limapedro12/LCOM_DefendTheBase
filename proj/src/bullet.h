#ifndef BULLET_H
#define BULLET_H

#include <lcom/lcf.h>
#include <math.h>
#include "our_framework/framework_essencials.h"

position bullet_pos[6];
int* bullet_enemy_id_ptr;

/**
 * @brief function that draws a bullet that is shot from a tower to hit an enemy
 * 
 * @param tower_x x coordinate of tower
 * @param tower_y y coordinate of tower
 * @param enemy_x x coordinate of enemy
 * @param enemy_y y coordinate of enemy
 * @param tower_id id of tower
 * @param enemy_id id of enemy
 * @param bullet_speed speed of bullet
 * @param bullet_range range of bullet
 * @param time_between_shots time between shots of bullet
 * @return false if bullet is not drawn
 */
bool drawBullet(int tower_x, int tower_y, int enemy_x, int enemy_y, int tower_id, int enemy_id, int bullet_speed, int bullet_range, int time_between_shots);

#endif
