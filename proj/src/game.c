#include "game.h"
#include "our_framework/framework_essencials.h"
#include "draw/draw.h"
#include "xpm/test.xpm"
#include "xpm/teapot.xpm"

int time_0;
bool menu_state = true;

int before(){
  turn_on_graphics();
  time_0 = get_time_counter();
  // printf("Hello World from inside Game!\n");
  return 0;
}

int x = 10;
int y = 10;
int enemy_x = 151;
int enemy_y = 300;

void game(){
  clear_screen();

  if(menu_state) {
    draw_rectangle(250, 190, 300, 50, 0x00e600);
    draw_rectangle(250, 290, 300, 50, 0x86592d);

    if(is_key_pressed_code(0x81)){
      quit();
    }

    if(is_key_pressed(ENTER, false)){
      menu_state = false;
    }

    if(get_mouse_position().x >= 250 && get_mouse_position().x <= 550 && -get_mouse_position().y >= 190 && -get_mouse_position().y <= 240 && is_lb_pressed()){
      menu_state = false;
    }

    //cursor
    draw_rectangle(get_mouse_position().x, -get_mouse_position().y, 10, 10, 0xFF0000);
  } 

  else {

    if(is_key_pressed_code(0x81)){
    // printf("Esc Key pressed outside!\n");
    quit();
    }
    if(is_key_pressed(' ', false)){
      // printf("Space Key pressed outside!\n");
      quit();
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

    
    if(enemy_x > 150)
      enemy_y += 3;
    
    if(enemy_y > 390)
      enemy_x -= 3;

    if(enemy_x < 40)
      enemy_y -= 3;

    if(enemy_y < 300)
      enemy_x += 3;

    // printf("Mouse position: (%d, %d)\n", get_mouse_position().x, get_mouse_position().y);

    // if(is_time_interval_elapsed_seconds(time_0, 5)){
    //   printf("5 seconds has passed!");
    //   quit();
    // }


    /* Draw Background */
    draw_rectangle(0, 0, 800, 600, 0x86592d);

    char map[12][16] = {
      {' ','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#'},
      {' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ','#','#','#','#'},
      {'#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ','#'},
      {'#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#',' ','#'},
      {'#',' ','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#'},
      {'#',' ','#','#',' ',' ',' ','#',' ','#','#','#','#','#','#','#'},
      {' ',' ','#','#',' ','#','#','#',' ','#','#',' ',' ',' ','#','#'},
      {' ','#','#','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ','#','#'},
      {' ','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#'},
      {' ',' ','#',' ',' ',' ',' ','#','#','#',' ','#','#',' ','#','#'},
      {'#',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ',' '},
      {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    };

    draw_map(map);

    draw_rectangle(x, y, 30, 30, 0xFFFF00);
    draw_rectangle(get_mouse_position().x, -get_mouse_position().y, 15, 15, 0xFF0000);
    draw_rectangle(enemy_x, enemy_y, 30, 30, 0x0000FF);
    
    //draw_xpm(100,100, teapot_xpm);


    // if(get_mouse_position().x > 0 && get_mouse_position().y > 0)
    //   draw_rectangle(300, 300, 30, 30, 0xFF0000);
    // else if(get_mouse_position().x > 0 && get_mouse_position().y < 0)
    //   draw_rectangle(300, -300, 30, 30, 0x00FF00);
    // else if(get_mouse_position().x < 0 && get_mouse_position().y > 0)
    //   draw_rectangle(-300, 300, 30, 30, 0x0000FF);
    // else if(get_mouse_position().x < 0 && get_mouse_position().y < 0)
    //   draw_rectangle(-300, -300, 30, 30, 0xFFFFFF);
  }
}

int after(){
  return 0;
}
