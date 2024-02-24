#ifndef KERNEL_INT_INTERNAL_H
#define KERNEL_INT_INTERNAL_H

#include "../types.h"

#define IDT_FLAG_GATE_TASK_32	   0x05
#define IDT_FLAG_GATE_INTERRUPT_16 0x06
#define IDT_FLAG_GATE_TRAP_16	   0x07
#define IDT_FLAG_GATE_INTERRUPT_32 0x0E
#define IDT_FLAG_GATE_TRAP_32	   0x0F

#define IDT_FLAG_RING_0 0x00
#define IDT_FLAG_RING_1 0x20
#define IDT_FLAG_RING_2 0x40
#define IDT_FLAG_RING_3 0x60

#define IDT_FLAG_PRESENT 0x80

#define INT_FAUL_DE 0  /* Divide Error */
#define INT_FAUL_DB 1  /* Debug Exception */
#define INT_INTR_NI 2  /* NMI Interrupt */
#define INT_TRAP_BP 3  /* Breakpoint */
#define INT_TRAP_OF 4  /* Overflow */
#define INT_FAUL_BR 5  /* BOUND Rage */
#define INT_FAUL_UD 6  /* Invalid Opcode */
#define INT_FAUL_NM 7  /* No Math Coprocessor*/
#define INT_FAUL_DF 8  /* Double Fault */
#define INT_FAUL_TS 9  /* Coprocessor Segment Overrun */
#define INT_FAUL_NP 10 /* Invalid TSS */
#define INT_FAUL_SS 11 /* Segment Not Present */
#define INT_FAUL_GP 12 /* Stack-Segment Fault */
#define INT_FAUL_PF 13 /* General Protection */
#define INT_FAUL_MF 14 /* Math Fault */
#define INT_FAUL_AC 15 /* Alignment Check */
#define INT_ABRT_MC 16 /* Machine Check */
#define INT_FAUL_XM 17 /* SIMD Floating-Point Exception */
#define INT_FAUL_VE 18 /* Virtualization Exception */
#define INT_FAUL_CP 19 /* Control Protection Exception */

#define INT_INTR_PTI 32 /* Programmable Timer */
#define INT_INTR_KBD 33 /* Keyboard Input */
#define INT_INTR_CSC 34 /* Cascade (wont be raised) */
#define INT_INTR_CO1 35 /* COM1 */
#define INT_INTR_CO2 36 /* COM2 */
#define INT_INTR_LP2 37 /* LPT2 */
#define INT_INTR_FLD 38 /* Floppy Disk */
#define INT_INTR_LP1 39 /* LPT1 */
#define INT_INTR_RTC 40 /* CMOS Realtime Clock */
#define INT_INTR_PH0 41 /* Free for peripherals / legacy scsi / nic */
#define INT_INTR_PH1 42 /* Free for peripherals / scsi / nic */
#define INT_INTR_PH2 43 /* Free for peripherals / scsi / nic */
#define INT_INTR_PS2 44 /* PS2 Mouse */
#define INT_INTR_FPU 45 /* FPU */
#define INT_INTR_PAT 46 /* Primary ATA Disk */
#define INT_INTR_SAT 47 /* Secondary ATA Disk */

#define INT_INTR_SYS 128 /* Syscall */

#define INT_PIC_REMAP 0x20

typedef struct {
	uint16 base_lo;
	uint16 segment_selector;
	uint8  _reserved0;
	uint8  flags;
	uint16 base_hi;
} __attribute__((packed)) KernelIdtEntry;

typedef struct {
	uint16		limit;
	KernelIdtEntry *table;
} __attribute__((packed)) KernelIdtDescriptor;

typedef struct {
	uint32 ds;

	uint32 edi;
	uint32 esi;
	uint32 epb;
	uint32 esp_kernel;
	uint32 ebx;
	uint32 edx;
	uint32 ecx;
	uint32 eax;

	uint32 interrupt;

	uint32 eip;
	uint32 cs;
	uint32 eflags;
	uint32 esp;
	uint32 ss;
} __attribute__((packed)) KernelIntStack;

/* fill the idt (part of setup routine) */
void kernel_idt_fill();

/* set an idt entry */
void kernel_idt_set_entry(uint8 interrupt, void *handler, uint8 flags,
			  uint16 segment_selector);

/* load idt */
void kernel_idt_load(const KernelIdtDescriptor *descp);

/* handle interrupts */
void kernel_int_handle(KernelIntStack *stack);

/* send end of interrupt */
void kernel_int_pic_eoi(uint8 irq);

/* =========== Interrupt Forwards =========== */

void kernel_int_ignore();

void kernel_isr_forward_0();
void kernel_isr_forward_32();
void kernel_isr_forward_33();
void kernel_isr_forward_34();
void kernel_isr_forward_35();
void kernel_isr_forward_36();
void kernel_isr_forward_37();
void kernel_isr_forward_38();
void kernel_isr_forward_39();
void kernel_isr_forward_40();
void kernel_isr_forward_41();
void kernel_isr_forward_42();
void kernel_isr_forward_43();
void kernel_isr_forward_44();
void kernel_isr_forward_45();
void kernel_isr_forward_46();
void kernel_isr_forward_47();
void kernel_isr_forward_128();

#endif
