#include "drag.h"

void verifyDrag(int * x, int * y){
  int tower_size = 50;
  if(is_lb_pressed() && *x>=get_mouse_position().x - tower_size  && *x<=get_mouse_position().x+tower_size &&*y>=get_mouse_position().y-tower_size && *y<=get_mouse_position().y+tower_size){
    *x = get_mouse_position().x;
    *y = get_mouse_position().y;
  }

  }

