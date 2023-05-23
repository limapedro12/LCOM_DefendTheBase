#include "bullet.h"

double bullet_x; 
double bullet_y;
bool is_bullet_on = false;

void drawBullet(int tower_x, int tower_y, int enemy_x, int enemy_y){
  int tower_x_center =  tower_x + 15;
  int tower_y_center = tower_y + 15;
  int enemy_x_center = enemy_x + 15;
  int enemy_y_center = enemy_y + 15;
  double y_difference = enemy_y_center - tower_y_center;
  double x_difference = enemy_x_center -  tower_x_center;
  if(sqrt(y_difference*y_difference + x_difference*x_difference) <= 200.0){
    if(!is_bullet_on) {
      is_bullet_on = true;
      bullet_x = tower_x; bullet_y = tower_y;
    } 
  } 
  if(is_bullet_on){
    draw_rectangle(bullet_x, bullet_y, 15, 15, 0xDDDDDD);
    // bullet center = buller coordinates + 7.5
    double move_delta_x = (bullet_x + 7.5 - enemy_x_center);
    double move_delta_y = (bullet_y + 7.5 - enemy_y_center);
    double move_delta = sqrt(move_delta_x*move_delta_x + move_delta_y*move_delta_y);
    move_delta_x /= move_delta;
    move_delta_y /= move_delta;
    bullet_x -= move_delta_x;
    bullet_y -= move_delta_y;
  }
  
  if(bullet_x + 7.5 >= enemy_x_center - 15 && bullet_x + 7.5 <= enemy_x_center + 15 &&
        bullet_y + 7.5 >= enemy_y_center - 15 && bullet_y + 7.5 <= enemy_y_center + 15) {
    is_bullet_on = false;
  }
}
