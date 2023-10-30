TARGET=
TOOLCHAIN=./Toolchain/$(TARGET)

CC=$(TOOLCHAIN)/bin/$(TARGET)-gcc
AS=$(TOOLCHAIN)/bin/$(TARGET)-as
LD=$(TOOLCHAIN)/bin/$(TARGET)-ld

CFLAGS=-std=c89 -nostdlib

KERNEL_OBJ=\
Kernel/boot/b_boot.o \
Kernel/boot/b_gdt.o \
Kernel/boot/b_multiboot.o \
Kernel/boot/b_stack.o

Kernel/boot/%.o: Kernel/boot/%.s
	$(AS) $< -o $@

i386: TARGET=i386-elf
i386: $(KERNEL_OBJ)
	$(LD) $(KERNEL_OBJ) -T Kernel/linker.ld -o kernel.bin
	strip kernel.bin
