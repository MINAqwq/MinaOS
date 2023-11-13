#include "v_internal.h"

static uint current_device;

void
kernel_video_init(uint device)
{
	switch (device) {
	case KERNEL_VIDEO_DEVICE_VGA:
		kernel_video_vga_init();
		kernel_video_vga_set_color(0x5F);
		break;
	}

	current_device = device;
}

void
kernel_video_unload()
{
	switch (current_device) {
	case KERNEL_VIDEO_DEVICE_VGA:
		kernel_video_vga_clear();
		break;
	}

	current_device = -1;
}

void
kernel_video_print(const string str)
{
	uint i;

	switch (current_device) {
	case KERNEL_VIDEO_DEVICE_VGA:
		for (i = 0; str[i] != 0; i++) {
			kernel_video_vga_putc(str[i]);
		}
		break;
	}
}

void
kernel_video_print_hex(uint8 hexnum)
{
	char str[3];

	str[0] = ((hexnum >> 4) & 0xF) + (hexnum < 0xA ? '0' : '7');
	str[1] = (hexnum & 0xF) + (hexnum < 0xA ? '0' : '7');
	str[2] = 0;

	kernel_video_print((const string)&str);
}