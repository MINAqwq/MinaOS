.set KERNEL_MULTIBOOT_MAGIC, 0x1BADB002

.set KERNEL_MULTIBOOT_FLAG_ALIGN, 0x01
.set KENREL_MULTIBOOT_FLAGS, KERNEL_MULTIBOOT_FLAG_ALIGN

.set KERNEL_MULTIBOOT_CHECKSUM, -(KERNEL_MULTIBOOT_MAGIC + KENREL_MULTIBOOT_FLAGS)

.section .multiboot
.align 4
.long KERNEL_MULTIBOOT_MAGIC
.long KENREL_MULTIBOOT_FLAGS
.long KERNEL_MULTIBOOT_CHECKSUM
