#include "game.h"
#include "our_framework/framework_essencials.h"

int before(){
    return 0;
}

void game(){
    printf("Hello World from inside Game!");
    quit();
}

int after(){
    return 0;
}
