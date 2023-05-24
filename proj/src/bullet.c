#include "bullet.h"
#include "xpm/shot_orange.xpm"

double bullet_x; 
double bullet_y;
position bullet_pos[6];
int bullet_enemy_id[6] = {-1, -1, -1, -1, -1, -1};
int last_time_a_bullet_was_shot[6] = {-1, -1, -1, -1, -1, -1};
bool is_bullet_on = false;
// int time_between_shots = 700;
// int bullet_speed = 5;
// int bullet_range = 100;

bool drawBullet(int tower_x, int tower_y, int enemy_x, int enemy_y, int tower_id, int enemy_id, int bullet_speed, int bullet_range, int time_between_shots){
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
  if(sqrt(y_difference*y_difference + x_difference*x_difference) <= bullet_range){
    if(bullet_enemy_id[tower_id] == -1 && 
      is_time_interval_elapsed_milliseconds(last_time_a_bullet_was_shot[tower_id], time_between_shots)) {
      bullet_enemy_id[tower_id] = enemy_id;
      bullet_pos[tower_id].x = tower_x_center; 
      bullet_pos[tower_id].y = tower_y_center;
      last_time_a_bullet_was_shot[tower_id] = get_time_counter();
    } 
  } 

  if(bullet_enemy_id[tower_id] == enemy_id){
    if(bullet_pos[tower_id].x < 0 || bullet_pos[tower_id].x > 800 || 
       bullet_pos[tower_id].y < 0 || bullet_pos[tower_id].y > 600){
      bullet_enemy_id[tower_id] = -1;
      return false;
    }
    draw_xpm(bullet_pos[tower_id].x, bullet_pos[tower_id].y, shot_orange, 0xFFFFFF);
    // bullet center = bullet coordinates + 7.5
    double move_delta_x = (bullet_pos[tower_id].x + 7.5 - enemy_x_center)/5;
    double move_delta_y = (bullet_pos[tower_id].y + 7.5 - enemy_y_center)/5;

    double move_delta = sqrt(move_delta_x*move_delta_x + move_delta_y*move_delta_y);
    move_delta_x /= move_delta;
    move_delta_y /= move_delta;
    bullet_pos[tower_id].x -= bullet_speed*move_delta_x;
    bullet_pos[tower_id].y -= bullet_speed*move_delta_y;
  }
  
  if(bullet_pos[tower_id].x + 7.5 >= enemy_x_center - 15 && 
     bullet_pos[tower_id].x + 7.5 <= enemy_x_center + 15 &&
     bullet_pos[tower_id].y + 7.5 >= enemy_y_center - 15 && 
     bullet_pos[tower_id].y + 7.5 <= enemy_y_center + 15) {
    bullet_enemy_id[tower_id] = -1;
    return true;
  }
  return false;
}
