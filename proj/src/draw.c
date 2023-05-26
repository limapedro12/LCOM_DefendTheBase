#include "draw.h"

extern position bullet_pos[4];

void load_xpms(){
    background_pixmap = xpm_load(background_xpm, XPM_8_8_8, &background_img);
    menu_pixmap = xpm_load(menu_xpm, XPM_8_8_8, &menu_img);
    tower_orange_up_right_pixmap = xpm_load(tower_orange_up_right, XPM_8_8_8, &tower_orange_up_right_img);
    tower_orange_right_pixmap = xpm_load(tower_orange_right, XPM_8_8_8, &tower_orange_right_img);
    tower_orange_down_right_pixmap = xpm_load(tower_orange_down_right, XPM_8_8_8, &tower_orange_down_right_img);
    tower_orange_down_pixmap = xpm_load(tower_orange_down, XPM_8_8_8, &tower_orange_down_img);
    tower_orange_down_left_pixmap = xpm_load(tower_orange_down_left, XPM_8_8_8, &tower_orange_down_left_img);
    tower_orange_left_pixmap = xpm_load(tower_orange_left, XPM_8_8_8, &tower_orange_left_img);
    tower_orange_up_left_pixmap = xpm_load(tower_orange_up_left, XPM_8_8_8, &tower_orange_up_left_img);
    tower_orange_up_pixmap = xpm_load(tower_orange_up, XPM_8_8_8, &tower_orange_up_img);
}

void draw_map(char map[12][16]) {

    for(int y = 0; y <= 12; y++) {
        for(int x = 0; x <= 16; x++) {
            if(map[y][x] == '#') {
                draw_rectangle(x*50, y*50, 50, 50, 0x00e600);
            }
            if(map[y][x] == '-') {
                draw_rectangle(x*50, y*50, 50, 50, 0x000000);
            }
        }
    }
}

void draw_lives(int lives) {
    switch (lives)
    {
    case 1:
        draw_rectangle(620, 300, 30, 30, 0xFF0000);
        break;
    
    case 2:
        draw_rectangle(620, 300, 30, 30, 0xFF0000);
        draw_rectangle(620, 350, 30, 30, 0xFF0000);
        break;

    case 3:
        draw_rectangle(620, 300, 30, 30, 0xFF0000);
        draw_rectangle(620, 350, 30, 30, 0xFF0000);
        draw_rectangle(620, 400, 30, 30, 0xFF0000);
        break;          
    default:
        break;
    }
}

void draw_tower(int tower_id, int tower_x, int tower_y){
    int delta_x;
    int delta_y;
    if(false) {
        delta_x = tower_x - get_mouse_position().x;
        delta_y = tower_y - get_mouse_position().y;
    } else {
        delta_x = tower_x - bullet_pos[tower_id].x;
        delta_y = tower_y - bullet_pos[tower_id].y;
    }
    int angle = atan2(delta_y, delta_x) * 180 / 3.1416;
    if(angle > 22.5 && angle < 67.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_up_right, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_up_right_pixmap, tower_orange_up_right_img, 0xFFFFFF);
    else if(angle > 67.5 && angle < 112.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_right, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_right_pixmap, tower_orange_right_img, 0xFFFFFF);
    else if(angle > 112.5 && angle < 157.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_down_right, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_down_right_pixmap, tower_orange_down_right_img, 0xFFFFFF);
    else if(angle > 157.5 || angle < -157.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_down, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_down_pixmap, tower_orange_down_img, 0xFFFFFF);
    else if(angle > -157.5 && angle < -112.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_down_left, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_down_left_pixmap, tower_orange_down_left_img, 0xFFFFFF);
    else if(angle > -112.5 && angle < -67.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_left, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_left_pixmap, tower_orange_left_img, 0xFFFFFF);
    else if(angle > -67.5 && angle < -22.5)
        /* draw_xpm(tower_x, tower_y, tower_orange_up_left, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_up_left_pixmap, tower_orange_up_left_img, 0xFFFFFF);
    else
        /* draw_xpm(tower_x, tower_y, tower_orange_up, 0xFFFFFF); */
        draw_xpm_loaded(tower_x, tower_y, tower_orange_up_pixmap, tower_orange_up_img, 0xFFFFFF);
}
