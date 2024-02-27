#include "memhelp.h"

void
kernel_utils_memcpy(void *dst, void *src, uint32 size)
{
	while (size--) {
		*(((uint8 *)dst) + size) = *(((uint8 *)src) + size);
	}
}

void
kernel_utils_memset(void *x, uint8 val, uint32 size)
{
	while (size--) {
		*((uint8 *)x) = val;
	}
}
