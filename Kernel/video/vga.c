#include "internal.h"

static uint16 *vga_buffer;
static uint16  vga_row;
static uint16  vga_col;
static uint16  vga_color;

static const uint16 vga_max_rows = 25;
static const uint16 vga_max_cols = 80;

void
kernel_video_vga_init()
{
	vga_buffer = (uint16 *)0xb8000;
	vga_row = 0;
	vga_col = 0;
}

void
kernel_video_vga_clear()
{
	uint16 i;
	uint16 j;

	/* iterate over whole screen buffer and clear it */
	for (i = 0; i < vga_max_rows; i++) {
		for (j = 0; j < vga_max_cols; j++) {
			vga_buffer[j * vga_max_rows + i] = 0;
		}
	}
}

void
kernel_video_vga_set_color(uint8 color)
{
	uint16 i;
	uint16 j;

	vga_color = color;

	for (i = 0; i < vga_max_rows; i++) {
		for (j = 0; j < vga_max_cols; j++) {
			((uint8 *)&vga_buffer[i * vga_max_cols + j])[1] =
			    vga_color;
		}
	}
}

void
kernel_video_vga_putc(char c)
{
	if (c == '\n') {
		vga_row++;
		vga_col = 0;
		if (vga_row == vga_max_rows) {
			vga_row--;
			kernel_video_vga_push();
		}
		return;
	}

	vga_buffer[vga_row * vga_max_cols + vga_col] = ((vga_color << 8) | c);
	vga_col++;

	if (vga_col == vga_max_cols) {
		vga_row++;
		vga_col = 0;
	}
}

void
kernel_video_vga_push()
{
	uint8 i;
	uint8 j;

	/* shift all rows 1 row up lol */
	for (i = 1; i < vga_max_rows; i++) {
		for (j = 0; j < vga_max_cols; j++) {
			vga_buffer[(i - 1) * vga_max_cols + j] =
			    vga_buffer[i * vga_max_cols + j];
		}
	}

	/* clear last line */
	for (i = 0; i < vga_max_cols; i++) {
		vga_buffer[(vga_max_rows - 1) * vga_max_cols + i] =
		    (0 | (vga_color << 8));
	}
}
