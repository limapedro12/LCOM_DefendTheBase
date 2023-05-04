#include "draw.h"
#include "our_framework/framework_essencials.h"

void draw_map(char map[12][16]) {

    for(int y = 0; y <= 12; y++) {
        for(int x = 0; x <= 16; x++) {
            if(map[y][x] == '#') {
                draw_rectangle(x*50, y*50, 50, 50, 0x00e600);
            }
        }
    }
}
