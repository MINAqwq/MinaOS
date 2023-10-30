/* global descriptor table */

.global _gdtr
.global _gdt_load

.text

_gdt_start:

/* null descriptor */
_gdt_kernel_nullseg:
.quad 0

/* flat kerne code segment
 * Base = 0
 * Limit = 0xFFFFF
 * Access Byte = 0x9A
 * Flags = 0xC
*/
_gdt_kernel_codeseg:
.short 0xFFFF
.short 0x0000
.byte  0x00
.byte  0x9A
.byte  0xCF
.byte  0x00

/* flat kernel data segment
 * Base = 0
 * Limit = 0xFFFFF
 * Access Byte = 0x92
 * Flags = 0xC
*/
_gdt_kernel_dataseg:
.short 0xFFFF
.short 0x0000
.byte  0x00
.byte  0x92
.byte  0xCF
.byte  0x00

/* flat user code segment
 * Base = 0
 * Limit = 0xFFFFF
 * Access Byte = 0xFA
 * Flags = 0xC
*/
_gdt_user_codeseg:
.short 0xFFFF
.short 0x0000
.byte  0x00
.byte  0xFA
.byte  0xCF
.byte  0x00

/* flat user data segment
 * Base = 0
 * Limit = 0xFFFFF
 * Access Byte = 0xF2
 * Flags = 0xC
*/
_gdt_user_dataseg:
.short 0xFFFF
.short 0x0000
.byte  0x00
.byte  0xF2
.byte  0xCF
.byte  0x00

_gdt_end:

_gdtr:
    .short (_gdt_end - _gdt_start)
    .long _gdt_start

/* tell cpu where the gdt is located */
.type _gdt_load, @function
_gdt_load:
    lgdt (_gdtr)
    ret
