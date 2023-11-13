#ifndef KERNEL_V_INTERNAL_H
#define KERNEL_V_INTERNAL_H

#include "video.h"

/* ============ VGA ============ */
void kernel_video_vga_init();

void kernel_video_vga_clear();

void kernel_video_vga_set_color(uint8 color);

void kernel_video_vga_putc(char c);

void kernel_video_vga_putc_ext(char c, uint8 color);

void kernel_video_vga_push();

#endif
