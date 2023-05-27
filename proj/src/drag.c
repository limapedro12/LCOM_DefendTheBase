#include "drag.h"

void verifyDrag(int * x, int * y, bool * new, bool * new_next, bool * placed, bool * placed_next, int * coins, uint8_t* background_pixmap, xpm_image_t background_img){
  int tower_size = 30;
  if(placed && is_lb_pressed() && *x>=get_mouse_position().x - tower_size  && *x<=get_mouse_position().x+tower_size &&*y>=get_mouse_position().y-tower_size && *y<=get_mouse_position().y+tower_size){
    *x = get_mouse_position().x - 15;
    *y = get_mouse_position().y - 15;
  }
  if(is_key_pressed('p', false) && *x>=get_mouse_position().x - tower_size  && *x<=get_mouse_position().x+tower_size &&*y>=get_mouse_position().y-tower_size && *y<=get_mouse_position().y+tower_size) {
    *x = ((*x + 15) / 50) * 50;
    *y = ((*y + 15) / 50) * 50;
    *placed = true;
    *placed_next = false;
    *new = false;
    *new_next = true;
    *coins = *coins - 50;
    highlight_map(*x + 25, *y +25, 120, background_pixmap, background_img);
  }
}

void verifyUpgrade(int * x, int * y, int * level, int * coins){
  int tower_size = 30;
  if(is_key_pressed('u', true) && *x>=get_mouse_position().x - tower_size  && *x<=get_mouse_position().x+tower_size &&*y>=get_mouse_position().y-tower_size && *y<=get_mouse_position().y+tower_size){
    
    if(*level == 1) {*level = 2;}
    else if(*level == 2) {*level = 3;}

    *coins = *coins -100;
  }
}
