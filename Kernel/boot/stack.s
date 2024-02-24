/* kernel stack */

.global kernel_boot_stack_top

.section .bss
.align 16

kernel_boot_stack_bottom:
.skip 16384 # 16 KiB

kernel_boot_stack_top:
