#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include "our_framework/framework_essencials.h"
#include "bullet.h"
#include "xpm/tower_orange_up.xpm"
#include "xpm/tower_orange_right_up.xpm"
#include "xpm/tower_orange_right.xpm"
#include "xpm/tower_orange_right_down.xpm"
#include "xpm/tower_orange_down.xpm"
#include "xpm/tower_orange_left_down.xpm"
#include "xpm/tower_orange_left.xpm"
#include "xpm/tower_orange_left_up.xpm"

void draw_map(char map[12][16]);

void draw_lives(int lives);

void draw_tower(int tower_id, int tower_x, int tower_y);

#endif
