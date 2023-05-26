#ifndef GPU_H
#define GPU_H

#include <lcom/lcf.h>
uint NO_BACKGROUND;

void* (vg_init)(u16_t mode);
void draw_pixel(int x, int y, uint color);
void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint16_t mode);
int get_width(uint16_t mode);
int get_height(uint16_t mode);
int gpu_exit();
int doublebuffer_to_vram();
int draw_xpm(uint16_t x, uint16_t y, xpm_map_t xpm, uint color_to_ignore);
int draw_xpm_loaded(uint16_t x, uint16_t y, uint8_t* xpm, xpm_image_t img, uint color_to_ignore);
#endif
