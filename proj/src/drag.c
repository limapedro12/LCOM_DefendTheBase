#include "drag.h"

void verifyDrag(int * x, int * y, bool * placed, bool * placed_next){
  int tower_size = 30;
  if(placed && is_lb_pressed() && *x>=get_mouse_position().x - tower_size  && *x<=get_mouse_position().x+tower_size &&*y>=get_mouse_position().y-tower_size && *y<=get_mouse_position().y+tower_size){
    *x = get_mouse_position().x - 15;
    *y = get_mouse_position().y - 15;
  }
  if(is_key_pressed('p', false) && *x>=get_mouse_position().x - tower_size  && *x<=get_mouse_position().x+tower_size &&*y>=get_mouse_position().y-tower_size && *y<=get_mouse_position().y+tower_size) {
    *x = ((*x + 15) / 50) * 50 + 10;
    *y = ((*y + 15) / 50) * 50 + 10;
    *placed = true;
    *placed_next = false;
  }
}
