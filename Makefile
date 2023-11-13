TARGET=i386-elf
TOOLCHAIN=./Toolchain/$(TARGET)

CC=$(TOOLCHAIN)/bin/$(TARGET)-gcc
AS=$(TOOLCHAIN)/bin/$(TARGET)-as
LD=$(TOOLCHAIN)/bin/$(TARGET)-ld

CFLAGS=-std=c89 -nostdlib -ffreestanding

KERNEL_OBJ=\
Kernel/boot/b_boot.o \
Kernel/boot/b_gdt.o \
Kernel/boot/b_multiboot.o \
Kernel/boot/b_stack.o \
Kernel/interrupts/int_handler.o \
Kernel/interrupts/int_idt.o \
Kernel/interrupts/int_idt0.o \
Kernel/interrupts/int_isr.o \
Kernel/interrupts/int_irq.o \
Kernel/interrupts/int_pic.o \
Kernel/ports/p_io.o \
Kernel/video/v_abstract.o \
Kernel/video/v_vga.o \
Kernel/k_error.o\
Kernel/k_main.o

kernel: $(KERNEL_OBJ)
	$(LD) $(KERNEL_OBJ) -T Kernel/linker.ld -o kernel.bin
	strip kernel.bin

all: kernel


.PHONY:
kernel-clean:
	rm $(KERNEL_OBJ)
