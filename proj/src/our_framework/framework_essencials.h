#ifndef FRAMEWORK_ESSENCIALS_H
#define FRAMEWORK_ESSENCIALS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include "device_handlers/timer.h"

/**
 * @brief Runs the game
 * 
 * This function runs the function given as a parameter 60 times per second and responds to I/O interrupts.
 * 
 * @param func 
 * @return int 
 */
int run(void (*func)());

/**
 * @brief Quits the game
 * 
 * This function sets the game_running variable to false, which will cause the run function to stop running.
 * 
 */
void quit();

int get_time_counter();
bool is_time_interval_elapsed_seconds(int start_time, int interval);
bool is_time_interval_elapsed_milliseconds(int start_time, int interval);

#endif
