#include "bullet.h"

double bullet_x; 
double bullet_y;
position bullet_pos[6];
int bullet_enemy_id[6] = {-1, -1, -1, -1, -1, -1};
bool is_bullet_on = false;

bool drawBullet(int tower_x, int tower_y, int enemy_x, int enemy_y, int tower_id, int enemy_id){
  if(bullet_enemy_id[tower_id] != -1 && 
     enemy_id != bullet_enemy_id[tower_id]){
    return false;
  }

  int tower_x_center =  tower_x + 15;
  int tower_y_center = tower_y + 15;
  int enemy_x_center = enemy_x + 15;
  int enemy_y_center = enemy_y + 15;
  double y_difference = enemy_y_center - tower_y_center;
  double x_difference = enemy_x_center -  tower_x_center;
  if(sqrt(y_difference*y_difference + x_difference*x_difference) <= 100.0){
    if(bullet_enemy_id[tower_id] == -1) {
      bullet_enemy_id[tower_id] = enemy_id;
      bullet_pos[tower_id].x = tower_x; 
      bullet_pos[tower_id].y = tower_y;
    } 
  } 

  if(bullet_enemy_id[tower_id] == enemy_id){
    if(bullet_pos[tower_id].x < 0 || bullet_pos[tower_id].x > 800 || 
       bullet_pos[tower_id].y < 0 || bullet_pos[tower_id].y > 600){
      bullet_enemy_id[tower_id] = -1;
      return false;
    }
    draw_rectangle(bullet_pos[tower_id].x, bullet_pos[tower_id].y, 15, 15, 0xDDDDDD);
    // bullet center = bullet coordinates + 7.5
    double move_delta_x = (bullet_pos[tower_id].x + 7.5 - enemy_x_center)/5;
    double move_delta_y = (bullet_pos[tower_id].y + 7.5 - enemy_y_center)/5;
    double move_delta = sqrt(move_delta_x*move_delta_x + move_delta_y*move_delta_y);
    move_delta_x /= move_delta;
    move_delta_y /= move_delta;
    bullet_pos[tower_id].x -= 10*move_delta_x;
    bullet_pos[tower_id].y -= 10*move_delta_y;
  }
  
  if(bullet_pos[tower_id].x + 7.5 >= enemy_x_center - 15 && 
     bullet_pos[tower_id].x + 7.5 <= enemy_x_center + 15 &&
     bullet_pos[tower_id].y + 7.5 >= enemy_y_center - 15 && 
     bullet_pos[tower_id].y + 7.5 <= enemy_y_center + 15) {
    bullet_enemy_id[tower_id] = -1;
  }
  return true;
}
