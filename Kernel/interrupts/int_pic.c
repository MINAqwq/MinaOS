#include "../ports/ports.h"
#include "../video/video.h"
#include "int_internal.h"

#define PORT_PIC_M_COMMAND 0x20
#define PORT_PIC_M_DATA	   0x21
#define PORT_PIC_S_COMMAND 0xA0
#define PORT_PIC_S_DATA	   0xA1

void
kernel_int_pic_setup()
{
	uint8 i;

	kernel_video_print("PIC: icw1\n");

	/* icw1 - start init */
	kernel_ports_outb(0x11, PORT_PIC_M_COMMAND);
	kernel_ports_iowait();

	kernel_ports_outb(0x11, PORT_PIC_S_COMMAND);
	kernel_ports_iowait();

	kernel_video_print("PIC: icw2\n");

	/* icw2 - offsets */
	kernel_ports_outb(INT_PIC_REMAP, PORT_PIC_M_DATA);
	kernel_ports_iowait();

	kernel_ports_outb(INT_PIC_REMAP + 0x08, PORT_PIC_S_DATA);
	kernel_ports_iowait();

	kernel_video_print("PIC: icw3\n");

	/* icw3 - set slave on IRQ2 and give slave cascade mode */
	kernel_ports_outb(0x04, PORT_PIC_M_DATA);
	kernel_ports_iowait();

	kernel_ports_outb(0x02, PORT_PIC_S_DATA);
	kernel_ports_iowait();

	kernel_video_print("PIC: icw4\n");

	/* icw4 - 8086 mode */
	kernel_ports_outb(0x01, PORT_PIC_M_DATA);
	kernel_ports_iowait();

	kernel_ports_outb(0x01, PORT_PIC_S_DATA);
	kernel_ports_iowait();

	kernel_video_print("PIC: unmask all interrupts\n");

	/* clear data registers */
	kernel_ports_outb(0x00, PORT_PIC_M_DATA);
	kernel_ports_iowait();

	kernel_ports_outb(0x00, PORT_PIC_S_DATA);
	kernel_ports_iowait();
}

void
kernel_int_pic_mask(uint8 irq)
{
	uint8 port;
	uint8 mask;

	if (irq < 8) {
		port = PORT_PIC_M_DATA;
	} else {
		port = PORT_PIC_S_DATA;
		irq -= 8;
	}

	mask = kernel_ports_inb(port);

	/* not enough budget for format printing :c */
	kernel_video_print("PIC: inb mask -> ");
	kernel_video_print_hex(mask);
	kernel_video_print("\n");

	kernel_ports_outb(mask | (1 << irq), port);
}

void
kernel_int_pic_unmask(uint8 irq)
{
	uint8 port;
	uint8 mask;

	if (irq < 8) {
		port = PORT_PIC_M_DATA;
	} else {
		port = PORT_PIC_S_DATA;
		irq -= 8;
	}

	mask = kernel_ports_inb(port);

	kernel_video_print("PIC: inb mask -> ");
	kernel_video_print_hex(mask);
	kernel_video_print("\n");

	kernel_ports_outb(mask & ~(1 << irq), port);
}

void
kernel_int_pic_disable()
{
	kernel_video_print("PIC: Disabling...");
	kernel_ports_outb(0xFF, PORT_PIC_M_DATA);
	kernel_ports_outb(0xFF, PORT_PIC_S_DATA);
}

void
kernel_int_pic_eoi(uint8 irq)
{
	kernel_ports_outb(0x20,
			  irq < 8 ? PORT_PIC_M_COMMAND : PORT_PIC_S_COMMAND);
}

void
kernel_int_pic_get_irr_register(uint8 *reg)
{
	kernel_ports_outb(0x0A, PORT_PIC_M_COMMAND);
	kernel_ports_outb(0x0A, PORT_PIC_S_COMMAND);

	reg[0] = kernel_ports_inb(PORT_PIC_M_COMMAND);
	reg[1] = kernel_ports_inb(PORT_PIC_S_COMMAND);
}

void
kernel_int_pic_get_isr_register(uint8 *reg)
{
	kernel_ports_outb(0x0B, PORT_PIC_M_COMMAND);
	kernel_ports_outb(0x0B, PORT_PIC_S_COMMAND);

	reg[0] = kernel_ports_inb(PORT_PIC_M_COMMAND);
	reg[1] = kernel_ports_inb(PORT_PIC_S_COMMAND);
}
