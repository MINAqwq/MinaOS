#ifndef KERNEL_V_VIDEO_H
#define KERNEL_V_VIDEO_H

#include "../types.h"

#define KERNEL_VIDEO_DEVICE_VGA 0x00

/* initialize video device */
void kernel_video_init(uint device);

/* unload current video device */
void kernel_video_unload();

/* print a null delimited string on the screen */
void kernel_video_print(const string str);

/* prints 2 hexadeciaml digits on the screen */
void kernel_video_print_hex(uint8 hexnum);

#endif
