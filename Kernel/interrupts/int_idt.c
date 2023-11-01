#include "int_internal.h"

/* pointer to idt descriptor */
static KernelIdtDescriptor kernel_int_descriptor;

/* entry array */
static KernelIdtEntry kernel_int_idt[256];

void
kernel_int_setup()
{
	/* setup idt descriptor */
	kernel_int_descriptor.limit = sizeof(kernel_int_idt) - 1;
	kernel_int_descriptor.table = (KernelIdtEntry *)&kernel_int_idt;

	/* fill the table */
	kernel_idt_fill();

	/* load the idt */
	kernel_idt_load(&kernel_int_descriptor);

	/* enable interrupts */
	kernel_int_enable();
}

void
kernel_idt_fill()
{
	uint i;

	for (i = 0; i < 256; i++) {
		kernel_idt_set_entry(i, &kernel_int_ignore,
				     IDT_FLAG_RING_0 |
					 IDT_FLAG_GATE_INTERRUPT_32 |
					 IDT_FLAG_PRESENT,
				     0x8);
	}

	kernel_idt_set_entry(INT_INTR_PTI, &kernel_isr_forward_32,
			     IDT_FLAG_RING_0 | IDT_FLAG_GATE_INTERRUPT_32 |
				 IDT_FLAG_PRESENT,
			     0x8);

	kernel_idt_set_entry(INT_INTR_KBD, &kernel_isr_forward_33,
			     IDT_FLAG_RING_0 | IDT_FLAG_GATE_INTERRUPT_32 |
				 IDT_FLAG_PRESENT,
			     0x8);
}

void
kernel_idt_set_entry(uint8 interrupt, void *handler, uint8 flags,
		     uint16 segment_selector)
{
	KernelIdtEntry *e;

	e = &kernel_int_idt[interrupt];
	e->base_hi = (((uint32)handler) >> 16);
	e->base_lo = (((uint32)handler) & 0xFFFF);
	e->flags = flags;
	e->segment_selector = segment_selector;
	e->_reserved0 = 0;
}
