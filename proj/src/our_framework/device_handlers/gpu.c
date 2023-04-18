#include "gpu.h"

void* (vg_init)(u16_t mode){
    // Get Info
    vbe_mode_info_t info;
    vbe_get_mode_info(mode, &info);

    // Get Phisical Address to Virtual Space
    long bytes_per_pixel = info.BitsPerPixel/8 + (info.BitsPerPixel%8 != 0);
    unsigned int vram_base = info.PhysBasePtr;	
    unsigned int vram_size = info.XResolution * info.YResolution * bytes_per_pixel;  

    struct minix_mem_range mr;
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size*2;

    int response;

    if( OK != (response = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", response);

    /* Map memory */

    void* video_mem = vm_map_phys(SELF, (void* ) mr.mr_base, vram_size);

    memset(video_mem,0,vram_size);

    if(video_mem == MAP_FAILED)
        panic("couldn't map video memory");


    // Set VBE Mode
    reg86_t r;
    memset(&r, 0, sizeof(r));
    r.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
    r.bx = 1<<14 | mode; // set bit 14: linear framebuffer
    r.intno = 0x10;
    if( sys_int86(&r) != OK ) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }

    return video_mem;
}

void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, void* buffer, uint16_t mode){
    char* ptr = (char* ) buffer;
    int bpp = 3; // get_bytes_per_pixel(mode);
    // if(bpp == 2) color = get_2B_color(color,mode);
    for(int i = x; i < x+width; i++)
        for(int j = y; j < y+height; j++)
            for(int k = 0; k < bpp; k++){
                ptr[j*get_width(mode)*bpp + i*bpp + k] = color >> (k*8);
            }
}

int get_width(uint16_t mode){
    vbe_mode_info_t info;
    vbe_get_mode_info(mode, &info);
    return info.XResolution;
}


