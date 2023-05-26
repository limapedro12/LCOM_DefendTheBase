#ifndef DRAG_H
#define DRAG_H
#include "lcom/lcf.h"
#include "our_framework/framework_essencials.h"

/**
 * @brief verifies if a tower is being dragged by the mouse
 * 
 * @param x x coordinate of the tower being dragged
 * @param y y coordinate of the tower being dragged
 * @param new checks if the tower is new
 * @param new_next allows you to place a new tower
 * @param placed checks if the tower is placed
 * @param placed_next allows you to place a new tower
 * @param coins checks if you have enough coins to place a tower
 */
void verifyDrag(int * x, int * y, bool * new, bool * new_next, bool * placed, bool * placed_next, int * coins);

/**
 * @brief verifies if a tower is being upgraded
 * 
 * @param x x coordinate of the tower being upgraded
 * @param y y coordinate of the tower being upgraded
 * @param level level of the tower being upgraded
 * @param coins checks if you have enough coins to upgrade a tower
 */
void verifyUpgrade(int * x, int * y, int * level, int * coins);

#endif
