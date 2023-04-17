#ifndef FRAMEWORK_ESSENCIALS_H
#define FRAMEWORK_ESSENCIALS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include "device_handlers/timer.h"
#include "device_handlers/kbd.h"

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

/**
 * @brief Get the current time counter
 * 
 * This function returns the current time counter, which is incremented 60 times per second.
 * It is used to "initialize" a timer that can be used to check if a certain amount of time has passed,
 * using the is_time_interval_elapsed_seconds and is_time_interval_elapsed_milliseconds functions.
 * 
 * @return int 
 */
int get_time_counter();

/**
 * @brief Checks if a certain amount of seconds has passed
 * 
 * This function checks if a certain amount of seconds has passed since the start_time.
 * 
 * @param start_time 
 * @param interval 
 * @return true 
 * @return false 
 */
bool is_time_interval_elapsed_seconds(int start_time, int interval);

/**
 * @brief Checks if a certain amount of milliseconds has passed
 * 
 * This function checks if a certain amount of milliseconds has passed since the start_time.
 * 
 * @param start_time 
 * @param interval 
 * @return true 
 * @return false 
 */
bool is_time_interval_elapsed_milliseconds(int start_time, int interval);

bool is_key_pressed(uint8_t scancode);

#endif
