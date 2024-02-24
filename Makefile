TARGET=i386-elf
TOOLCHAIN=./Toolchain/$(TARGET)

CC=$(TOOLCHAIN)/bin/$(TARGET)-gcc
AS=$(TOOLCHAIN)/bin/$(TARGET)-as
LD=$(TOOLCHAIN)/bin/$(TARGET)-ld

CFLAGS=-std=c89 -nostdlib -ffreestanding

KERNEL_OBJ=\
Kernel/boot/boot.o \
Kernel/boot/gdt.o \
Kernel/boot/multiboot.o \
Kernel/boot/stack.o \
Kernel/interrupts/interrupts.o \
Kernel/interrupts/idt.o \
Kernel/interrupts/idt0.o \
Kernel/interrupts/isr.o \
Kernel/interrupts/irq.o \
Kernel/interrupts/pic.o \
Kernel/ports/io.o \
Kernel/video/abstract.o \
Kernel/video/vga.o \
Kernel/error.o\
Kernel/main.o

kernel: $(KERNEL_OBJ)
	$(LD) $(KERNEL_OBJ) -T Kernel/linker.ld -o kernel.bin
	strip kernel.bin

all: kernel


.PHONY:
kernel-clean:
	rm $(KERNEL_OBJ)
