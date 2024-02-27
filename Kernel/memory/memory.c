#include "memory.h"

#include "../utils/memhelp.h"

static bool   page_register[0xbf000];
static uint32 page_register_base_addr = 0x1000000;

/* kernel page directory */
static PageDirectory kernel_memory_pd;

void
kernel_memory_pd_init()
{
	kernel_utils_memset(&kernel_memory_pd.entries, 0,
			    sizeof(kernel_memory_pd.entries));
}

PageDirectory *
kernel_memory_pd_get()
{
	return &kernel_memory_pd; 
}

void
kernel_memory_paging_init()
{
	kernel_memory_pd_init();
}

