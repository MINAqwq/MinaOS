#ifndef KERNEL_P_PORTS_H
#define KERNEL_P_PORTS_H

#include "../k_types.h"

/* write a byte to port */
void kernel_ports_outb(uint8 value, uint8 port);

/* read a byte from a port */
uint8 kernel_ports_inb(uint8 port);

/* io wait */
uint8 kernel_ports_iowait();

#endif
