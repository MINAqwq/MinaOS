#ifndef KERNEL_UTILS_MEMHELP_H
#define KERNEL_UTILS_MEMHELP_H

#include "../types.h"

/* copy size bytes from src to dst */
void kernel_utils_memcpy(void *dst, void *src, uint32 size);

/* set size bytes at x to val */
void kernel_utils_memset(void *x, uint8 val, uint32 size);

#endif
