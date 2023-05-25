#include "draw.h"
#include "our_framework/framework_essencials.h"

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
