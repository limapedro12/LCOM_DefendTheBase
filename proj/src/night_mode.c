#include "night_mode.h"

extern unsigned char* double_buffer;

uint8_t* highlighted_map;
xpm_image_t map_img;

uint8_t* shaded_map;

void start_night_mode(xpm_map_t map_xpm) {
  night_mode_filter = malloc((get_vram_size()/3)*sizeof(bool));
  for(int i = 0; i < get_vram_size()/3; i++)
    night_mode_filter[i] = 1;

  highlighted_map = xpm_load(map_xpm, XPM_8_8_8, &map_img);
}

void remove_hightlight() {
  for(int i = 0; i < get_vram_size()/3; i++)
    night_mode_filter[i] = 1;
}

void highlight_xpm_loaded(uint16_t x, uint16_t y, uint8_t* pixmap, xpm_image_t img, uint color_to_ignore){
  shaded_map = pixmap;
  for(int i = 0; i < img.height; i++)
    for(int j = 0; j < img.width; j++){
      unsigned int color = 0;
      for(int k = 0; k < 3; k++){
        color += ((uint) pixmap[i*img.width*3 + j*3 + k]) << (k*8);
      }
      
    if(color != color_to_ignore)
      night_mode_filter[(y+i)*800 + x+j] = 0;
  }
    
  return;
}

void apply_night_mode(){
  for(int i = 0; i < get_vram_size(); i++){
    double_buffer[i] >>= night_mode_filter[i/3];
  }
}

double get_value_to_multiply(){
  int hours = 1;
  int minutes = get_minutes();
  int combinacao = ((hours-3)%24)*60 + minutes;
  if(hours >= 15)
    combinacao = 1440 - combinacao;
  // if(combinacao > 600)
  //   combinacao = 600;
  // if(combinacao < 120)
  //   combinacao = 120;

  // combinacao -= 120;

  return (double) 0.5 + 0.5*((double) combinacao/(double) 480);
}

void apply_night_mode_on_xpm(uint8_t* pixmap, xpm_image_t img){
  for(int i = 0; i < img.height; i++)
    for(int j = 0; j < img.width; j++){
      for(int k = 0; k < 3; k++){
        pixmap[i*img.width*3 + j*3 + k] = highlighted_map[i*img.width*3 + j*3 + k] * get_value_to_multiply();
      }
    }
}

void highlight_map(int x, int y, int range, uint8_t* pixmap, xpm_image_t img){
  for(int i = x; i < range; i++)
    for(int j = y; j < range; j++){
      if(i >= 0 && i < map_img.width && j >= 0 && j < map_img.height)
        for(int k = 0; k < 3; k++){
            shaded_map[i*img.width*3 + j*3 + k] = highlighted_map[i*img.width*3 + j*3 + k];
        }
    }
}

