#ifndef BULLET_H
#define BULLET_H

#include <lcom/lcf.h>
#include <math.h>
#include "our_framework/framework_essencials.h"

bool drawBullet(int tower_x, int tower_y, int enemy_x, int enemy_y, int tower_id, int enemy_id, int bullet_speed, int bullet_range, int time_between_shots);

#endif
