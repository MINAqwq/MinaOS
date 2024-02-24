#ifndef KERNEL_INT_INTERRUPTS_H
#define KERNEL_INT_INTERRUPTS_H

#include "../types.h"

/* load the idt and setup interrrupts */
void kernel_int_setup();

/* enable interrupts */
void kernel_int_enable();

/* disable interrupts */
void kernel_int_disable();

/* ================== PIC ================== */

/* setup the pic */
void kernel_int_pic_setup();

/* mask irq */
void kernel_int_pic_mask(uint8 irq);

/* unmask an interrupt */
void kernel_int_pic_unmask(uint8 irq);

/* disable pic by masking (disabling) all interrupts */
void kernel_int_pic_disable();

/* write irr register from master and slave pic to byte array */
void kernel_int_pic_get_irr_register(uint8 *reg);

/* write isr register from master and slave pic to byte array */
void kernel_int_pic_get_isr_register(uint8 *reg);

#endif
