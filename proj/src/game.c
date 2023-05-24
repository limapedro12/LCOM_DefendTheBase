#include "game.h"
#include "our_framework/framework_essencials.h"
#include "draw/draw.h"
#include "xpm/test.xpm"
#include "xpm/cursor.xpm"
#include "xpm/tower_orange_right.xpm"
#include "xpm/tower_orange_up.xpm"
#include "player.h"
#include "drag.h"
#include "bullet.h"

int time_0;
int time_start_round;
bool menu_state = true;

int lives = 6;


int enemy_i = 0;

tower towers[6] = {{1, 610, 160, true, false}, {1, 610, 160, false, false}, {1, 610, 160, false, false}, {1, 610, 160, false, false}, {1, 610, 160, false, false}, {1, 610, 160, false, false}};

enemy enemies[6] = {{10, 10, 3}, {10, 10, 3}, {10, 10, 3}, {10, 10, 3}, {10, 10, 3}, {10, 10, 3}};
char enemy_directions[6] = {'d', 'd', 'd', 'd', 'd', 'd'};
int current_enemy_direction[6] = {0, 0, 0, 0, 0, 0};


position corners[13] = {{10, 60}, {510, 60}, {510, 210}, {360, 210}, {360, 360}, {210, 360}, {210, 210}, {60, 210}, {60, 510}, {510, 510}, {510, 360}, {660, 360}, {660, 510}};
char directions[13] = {'r', 'd', 'l', 'd', 'l', 'u', 'l', 'd', 'r', 'u', 'r', 'd', 'r'};
char direction = 'd';

bool game_clock = false;

int before(){

  turn_on_graphics();

  return 0;
}

void game(){
  clear_screen();
  verify_mouse_limits(0, 800-10, 0, 600-10);

  if(menu_state) {
    draw_rectangle(250, 190, 300, 50, 0x00e600);
    draw_rectangle(250, 290, 300, 50, 0x86592d);
    

    if(is_key_pressed(ESC, true)){
      quit();
    }

    if(is_key_pressed(ENTER, false)){
      menu_state = false;
      time_0 = get_time_counter();
    }

    if(get_mouse_position().x >= 250 && get_mouse_position().x <= 550 && get_mouse_position().y >= 190 && get_mouse_position().y <= 240 && is_lb_pressed()){
      menu_state = false;
      time_0 = get_time_counter();
    }
  } 

  else {

    /* Draw Background */
    draw_rectangle(0, 0, 800, 600, 0x86592d);

    char map[12][16] = {
      {' ','#','#','#','#','#','#','#','#','#','#','#','-','-','-','-'},
      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','-','-','-','-'},
      {'#','#','#','#','#','#','#','#','#','#',' ','#','-','-','-','-'},
      {'#','#','#','#','#','#','#','#','#','#',' ','#','-','-','-','-'},
      {'#',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','-','-','-','-'},
      {'#',' ','#','#',' ','#','#',' ','#','#','#','#','-','-','-','-'},
      {'#',' ','#','#',' ','#','#',' ','#','#','#','#','-','-','-','-'},
      {'#',' ','#','#',' ',' ',' ',' ','#','#',' ',' ','-','-','-','-'},
      {'#',' ','#','#','#','#','#','#','#','#',' ','#','-','-','-','-'},
      {'#',' ','#','#','#','#','#','#','#','#',' ','#','-','-','-','-'},
      {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','-','-','-','-'},
      {'#','#','#','#','#','#','#','#','#','#','#','#','-','-','-','-'},
    };

    draw_map(map);

    if(is_key_pressed(ESC, true)){
      quit();
    }

    if(is_key_pressed(' ', false)){
      game_clock = true;
      time_start_round = get_time_counter();
    }

    if(lives == 0) {
      quit();
    }

    if(game_clock) {
      int enemies_alive = 6;

      for(unsigned int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
        if(game_clock && is_time_interval_elapsed_seconds(time_start_round, i) && enemies[i].hp > 0){

          if(enemy_directions[i] == 'r') {
            enemies[i].x += 2;
          }
          if(enemy_directions[i] == 'l') {
            enemies[i].x -= 2;
          }
          if(enemy_directions[i] == 'u') {
            enemies[i].y -= 2;
          }
          if(enemy_directions[i] == 'd') {
            enemies[i].y += 2;
          }
              
          if(enemies[i].x == corners[current_enemy_direction[i]].x && 
            enemies[i].y == corners[current_enemy_direction[i]].y) {
            enemy_directions[i] = directions[current_enemy_direction[i]];
            current_enemy_direction[i]++;
          }

          if(enemies[i].x == 11*50+20 && enemies[i].y == 7*50+10) {
            lives--;
          }
        }

        if(!enemies[i].hp > 0) {
          enemies_alive--;
        }

        if(enemies_alive == 0) {
          game_clock = false;
        }
      }

      //Draw towerS
      for(unsigned int i = 0; i < sizeof(towers) / sizeof(towers[0]); i++) {
        if(towers[i].placed) {
          if(towers[i].level == 1) {
            draw_xpm(towers[i].x, towers[i].y, tower_orange_right, 0xFFFFFF);
          }         
          else {
            draw_xpm(towers[i].x, towers[i].y, tower_orange_up, 0xFFFFFF);
          }

          for(unsigned int j = 0; j < sizeof(enemies) / sizeof(enemies[0]);j++) {
            if(enemies[j].hp > 0 && drawBullet(towers[i].x, towers[i].y, enemies[j].x, enemies[j].y, i, j)){
              enemies[j].hp--;
            }
          }
        }
      }
    }

    else {

      for(unsigned int i = 0; i < sizeof(towers) / sizeof(towers[0]); i++) {
        if(towers[i].new) {
          draw_xpm(towers[i].x, towers[i].y, tower_orange_right, 0xFFFFFF);
          verifyDrag(&towers[i].x, &towers[i].y, &towers[i].new, &towers[i+1].new, &towers[i].placed, &towers[i+1].placed);
        }
        else {
          if(towers[i].placed) {
            if(towers[i].level == 1) {
              draw_xpm(towers[i].x, towers[i].y, tower_orange_right, 0xFFFFFF);
            }  
            else {
              draw_xpm(towers[i].x, towers[i].y, tower_orange_up, 0xFFFFFF);
            }      
            verifyUpgrade(&towers[i].x, &towers[i].y, &towers[i].level);
          }
        }
      }
    }

    //Draw enemies
    for(unsigned int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
      if(enemies[i].hp > 0 && enemies[i].x < 570 && enemies[i].y < 600) {
        draw_rectangle(enemies[i].x, enemies[i].y, 30, 30, 0x0000FF);
        draw_xpm(enemies[i].x, enemies[i].y, et_xpm, 0x000000);
      }
    }
  }
  
  draw_xpm(get_mouse_position().x, get_mouse_position().y, cursor, 0x2AFF00);
}

int after(){
  return 0;
}
