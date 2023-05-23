#include "game.h"
#include "our_framework/framework_essencials.h"
#include "draw/draw.h"
#include "xpm/test.xpm"
#include "xpm/teapot.xpm"
#include "xpm/cursor.xpm"
#include "player.h"
#include "drag.h"
#include "bullet.h"

int time_0;
int time_start_round;
bool menu_state = true;

int x = 10;
int y = 10;
int enemy_x = 10;
int enemy_y = 10;
position enemy_pos;
int enemy_i = 0;

position towers[6] = {{610, 160}, {610, 210}, {610, 260}, {660, 160}, {660, 210}, {660, 260}};
position enemies[6] = {{10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}};
char enemy_directions[6] = {'d', 'd', 'd', 'd', 'd', 'd'};
int current_enemy_direction[6] = {0, 0, 0, 0, 0, 0};

position corners[13] = {{10, 60}, {510, 60}, {510, 210}, {360, 210}, {360, 360}, {210, 360}, {210, 210}, {60, 210}, {60, 510}, {510, 510}, {510, 360}, {660, 360}, {660, 510}};
char directions[13] = {'r', 'd', 'l', 'd', 'l', 'u', 'l', 'd', 'r', 'u', 'r', 'd', 'r'};
char direction = 'd';

bool game_clock = false;

int before(){
  turn_on_graphics();

  enemy_pos.x = enemy_x;
  enemy_pos.y = enemy_y;

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

    if(is_key_pressed(ESC, true)){
      quit();
    }
    if(is_key_pressed(' ', false)){
      game_clock = true;
      time_start_round = get_time_counter();
    }

    if(is_key_pressed('a', false)){
      x-=6;
    }
    if(is_key_pressed('d', false)){
      x+=6;
    }
    if(is_key_pressed('w', false)){
      y-=3;
    }
    if(is_key_pressed('s', false)){
      y+=3;
    }

    if (x > 800-30)
      x = 800-30; 
    if (x < 0)
      x = 0;
    if (y > 600-30)
      y = 600-30;
    if (y < 0)
      y = 0;


    for(unsigned int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
      if(game_clock && is_time_interval_elapsed_seconds(time_start_round, i)){

        if(enemy_directions[i] == 'r') {
          enemies[i].x += 5;
        }
        if(enemy_directions[i] == 'l') {
          enemies[i].x -= 5;
        }
        if(enemy_directions[i] == 'u') {
          enemies[i].y -= 5;
        }
        if(enemy_directions[i] == 'd') {
          enemies[i].y += 5;
        }
            
        if(enemies[i].x == corners[current_enemy_direction[i]].x && 
          enemies[i].y == corners[current_enemy_direction[i]].y) {
          enemy_directions[i] = directions[current_enemy_direction[i]];
          current_enemy_direction[i]++;
        }

        if(enemies[i].x == 11*50+20 && enemies[i].y == 7*50+10) {
          quit();
        }
      }
    }

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

    //Draw player
    draw_rectangle(x, y, 30, 30, 0xFFFF00);


    //Draw towerS
    for(unsigned int i = 0; i < sizeof(towers) / sizeof(towers[0]); i++) {
      draw_rectangle(towers[i].x, towers[i].y, 30, 30, 0xFF0000);
      verifyDrag(&towers[i].x, &towers[i].y);
    }

    // drawBullet(towers[0].x, towers[0].y, enemies[5].x, enemies[5].y);
    for(unsigned int i = 0; i < sizeof(towers) / sizeof(towers[0]); i++) {
      // drawBullet(towers[i].x, towers[i].y, enemies[2].x, enemies[2].y);
      for(unsigned int j = 0; j < sizeof(enemies) / sizeof(enemies[0]);j++) {
        if(drawBullet(towers[i].x, towers[i].y, enemies[j].x, enemies[j].y, j))
          break;
      }
    }


    //Draw enemies
    for(unsigned int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
      draw_rectangle(enemies[i].x, enemies[i].y, 30, 30, 0x0000FF);
      draw_xpm(enemies[i].x, enemies[i].y, et_xpm, 0x000000);
    }

    draw_rectangle(enemies[2].x, enemies[2].y, 30, 30, 0xFFFFFF);
  }
  
  draw_xpm(get_mouse_position().x, get_mouse_position().y, cursor, 0x2AFF00);
}

int after(){
  return 0;
}
