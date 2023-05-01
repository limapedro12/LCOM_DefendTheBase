#ifndef GPU_H
#define GPU_H

#include <lcom/lcf.h>

void* (vg_init)(u16_t mode);
void draw_pixel(int x, int y, uint color);
void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint16_t mode);
int get_width(uint16_t mode);
int get_height(uint16_t mode);
int gpu_exit();
int doublebuffer_to_vram();
#endif
