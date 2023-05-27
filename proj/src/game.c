#include "game.h"
#include "our_framework/framework_essencials.h"
#include "draw.h"
#include "xpm/test.xpm"
#include "xpm/tower_purple/tower_purple.h"
#include "xpm/tower_orange/tower_orange.h"
#include "xpm/enemy_fire_skull/enemy_fire_skull_walking.h"
#include "player.h"
#include "drag.h"
#include "bullet.h"

int time_0;
int time_start_round;
bool menu_state = true;

bool game_clock = false;

int lives = 3;
int coins = 1000;

tower towers_level_1[6] = {{1, 605, 218, true, false}, {1, 605, 218, false, false}, {1, 605, 218, false, false}, {1, 605, 218, false, false}, {1, 605, 218, false, false}, {1, 605, 218, false, false}};
tower towers_level_2[6] = {{2, 672, 220, true, false}, {2, 672, 220, false, false}, {2, 672, 220, false, false}, {2, 672, 220, false, false}, {2, 672, 220, false, false}, {2, 672, 220, false, false}};


enemy enemies[4] = {{10, 10, 3}, {10, 10, 3}, {10, 10, 3}, {10, 10, 3}};
char enemy_directions[4] = {'d', 'd', 'd', 'd'};
int current_enemy_direction[4] = {0, 0, 0, 0};
int enemy_animation = 0;

position corners[13] = {{10, 60}, {510, 60}, {510, 210}, {360, 210}, {360, 360}, {210, 360}, {210, 210}, {60, 210}, {60, 510}, {510, 510}, {510, 360}, {660, 360}, {660, 510}};
char directions[13] = {'r', 'd', 'l', 'd', 'l', 'u', 'l', 'd', 'r', 'u', 'r', 'd', 'r'};
char direction = 'd';


int before(){

  turn_on_graphics();
  load_xpms();

  return 0;
}

void game(){
  clear_screen();
  verify_mouse_limits(0, 800-10, 0, 600-10);

  if(menu_state) {
    draw_xpm_loaded(0, 0, menu_pixmap, menu_img, NO_BACKGROUND);
    // draw_rectangle(250, 190, 300, 50, 0x00e600);
    // draw_rectangle(250, 290, 300, 50, 0x86592d);
    draw_xpm_loaded(257, 314, start_game_pixmap, start_game_img, 0xFFFFFF); //54, 281
    draw_xpm_loaded(341, 421, quit_pixmap, quit_img, 0xFFFFFF);//54, 114

    if(is_key_pressed(ESC, true)){
      quit();
    }

    if(is_key_pressed(ENTER, false)){
      menu_state = false;
      time_0 = get_time_counter();
    }

    if(get_mouse_position().x >= 257 && get_mouse_position().x <= 257 + 281 && 
       get_mouse_position().y >= 314 && get_mouse_position().y <= 314 + 54){
      draw_xpm_loaded(257, 314, start_game_glow_pixmap, start_game_glow_img, 0xFFFFFF);
      if(is_lb_pressed()){
        menu_state = false;
        time_0 = get_time_counter();
      }
    }
    if(get_mouse_position().x >= 341 && get_mouse_position().x <= 341 + 114&& 
       get_mouse_position().y >= 421 && get_mouse_position().y <= 421 + 54){
      draw_xpm_loaded(341, 421, quit_glow_pixmap, quit_glow_img, 0xFFFFFF);
      if(is_lb_pressed()){
        quit();
      }
    }
  } 

  else {

    /* Draw Background */
    // draw_rectangle(0, 0, 800, 600, 0x86592d);

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
    // draw_xpm_loaded(0, 0, background_pixmap, background_img, NO_BACKGROUND);

    if(is_key_pressed(ESC, true)){
      menu_state = true;
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
            enemies[i].hp = 0;
          }
        }

        if(!enemies[i].hp > 0) {
          enemies_alive--;
        }

        if(enemies_alive == 0) {
          for(unsigned int i = 0; i <= sizeof(enemies) / sizeof(enemies[0]); i++) {
            enemies[i].x = 10;
            enemies[i].y = 10;
            enemies[i].hp = 3;
            enemy_directions[i] = 'd';
            current_enemy_direction[i] = 0;
          }
          lives = 3;
          enemies_alive = 6;

          game_clock = false;
        }
      }

      //Draw towerS
      for(unsigned int i = 0; i < sizeof(towers_level_1) / sizeof(towers_level_1[0]); i++) {
        if(towers_level_1[i].placed) {
          int bullet_speed = 15*towers_level_1[i].level;
          int bullet_range = 300*towers_level_1[i].level;
          int bullet_time = 2000/towers_level_1[i].level;

          for(unsigned int j = 0; j < sizeof(enemies) / sizeof(enemies[0]);j++) {
            if(enemies[j].hp > 0 && drawBullet(towers_level_1[i].x, towers_level_1[i].y, enemies[j].x, enemies[j].y, i, j, bullet_speed, bullet_range, bullet_time)) {
              coins += 20;
              enemies[j].hp--;
            }
          }

          if(towers_level_1[i].level == 1) {
            draw_tower_directing_to_enemy(i, towers_level_1[i].x, towers_level_1[i].y, enemies, bullet_range);
            // draw_xpm(towers[i].x, towers[i].y, tower_orange_right, 0xFFFFFF);
          }         
          else {
            draw_xpm_loaded(towers_level_1[i].x, towers_level_1[i].y, tower_purple_right_pixmap, tower_purple_right_img, 0xFFFFFF);
          }
        }
      }
    }

    else {

      for(unsigned int i = 0; i < sizeof(towers_level_1) / sizeof(towers_level_1[0]); i++) {
        if(towers_level_1[i].new) {
          if(towers_level_1[i].level == 1) {
            draw_xpm_loaded(towers_level_1[i].x, towers_level_1[i].y, tower_orange_right_pixmap, tower_orange_right_img, 0xFFFFFF);
          }
          else if(towers_level_1[i].level == 2) {
            // draw_xpm(towers_level_1[i].x, towers_level_1[i].y, tower_purple_right, 0xFFFFFF);    
            draw_xpm_loaded(towers_level_1[i].x, towers_level_1[i].y, tower_purple_right_pixmap, tower_purple_right_img, 0xFFFFFF);        
          }
          
          if(coins >= 50) {
            verifyDrag(&towers_level_1[i].x, &towers_level_1[i].y, &towers_level_1[i].new, &towers_level_1[i+1].new, &towers_level_1[i].placed, &towers_level_1[i+1].placed, &coins);
          }
        }
        else {
          if(towers_level_1[i].placed) {
            if(towers_level_1[i].level == 1) {
              draw_xpm_loaded(towers_level_1[i].x, towers_level_1[i].y, tower_orange_right_pixmap, tower_orange_right_img, 0xFFFFFF);
            }  
            else {
              // draw_xpm(towers_level_1[i].x, towers_level_1[i].y, tower_purple_right, 0xFFFFFF);
            }      
            if(coins >= 100) {
              verifyUpgrade(&towers_level_1[i].x, &towers_level_1[i].y, &towers_level_1[i].level, &coins);
            }
          }
        }
      }

      for(unsigned int i = 0; i < sizeof(towers_level_2) / sizeof(towers_level_2[0]); i++) {
        if(towers_level_2[i].new) {
          if(towers_level_2[i].level == 2) {
            // draw_xpm(towers_level_2[i].x, towers_level_2[i].y, tower_purple_right, 0xFFFFFF);   
            draw_xpm_loaded(towers_level_2[i].x, towers_level_2[i].y, tower_purple_right_pixmap, tower_purple_right_img, 0xFFFFFF);
          }   
          if(coins >= 100) {
            verifyDrag(&towers_level_2[i].x, &towers_level_2[i].y, &towers_level_2[i].new, &towers_level_2[i+1].new, &towers_level_2[i].placed, &towers_level_2[i+1].placed, &coins);
          }
        }
        else {
          if(towers_level_2[i].placed) {
            if(towers_level_2[i].level == 2) {
              // draw_xpm(towers_level_2[i].x, towers_level_2[i].y, tower_purple_right, 0xFFFFFF);
              draw_xpm_loaded(towers_level_2[i].x, towers_level_2[i].y, tower_purple_right_pixmap, tower_purple_right_img, 0xFFFFFF);
            }    
            if(coins >= 200) {
              verifyUpgrade(&towers_level_2[i].x, &towers_level_2[i].y, &towers_level_1[i].level, &coins);
            }
          }
        }
      }
    }

    //Draw enemies
    for(unsigned int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
      if(enemies[i].hp > 0 && enemies[i].x < 570 && enemies[i].y < 600) {
        
        if(enemy_animation == 13) enemy_animation = 0;
        draw_xpm(enemies[i].x, enemies[i].y, enemy_fire_skull_walking[enemy_animation], 0xFFFFFF);
        enemy_animation++;

      }
    }

    draw_lives(lives);
  }

  draw_xpm_loaded(get_mouse_position().x, get_mouse_position().y, cursor_pixmap, cursor_img, 0x2AFF00);
}

int after(){
  return 0;
}
