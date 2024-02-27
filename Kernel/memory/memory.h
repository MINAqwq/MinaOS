/* Kernel Memory API */

#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include "../types.h"

/* =============== Paging =============== */

/* 4KiB */
#define PAGE_SIZE 0x1000

/* PDE pointing to 4KiB PT */
typedef struct {
	uint8  present : 1; /* present bit */
	uint8  rw : 1;	    /* read write */
	uint8  user : 1;    /* user mode */
	uint8  pwt : 1;	    /* write through cache */
	uint8  pcd : 1;	    /* disable page caching */
	uint8  a : 1;	    /* accessed (needs to be cleared by kernel) */
	uint8  _pad0 : 1;   /* padding */
	uint8  ps : 1;	    /* 0: 4KiB | 1: 4MiB */
	uint8  _pad1 : 4;   /* padding */
	uint32 addr : 20;   /* address to page table */
} PageDirectoryEntry;

/* 4KiB PTE */
typedef struct {
	uint8 present : 1; /* present bit */
	uint8 rw : 1;	   /* read write */
	uint8 user : 1;	   /* user mode */
	uint8 pwt : 1;	   /* write through cache */
	uint8 pcd : 1;	   /* disable page caching */
	uint8 a : 1;	   /* accessed (1 if accessed by mmu) */
	uint8 dirty : 1;   /* dirty (better accessed) */
	uint8 pat : 1;	   /* page attribute table */
	uint8 global : 1;  /* global page (won't invalidate the tlb entry after
			      mov to CR3) */
	uint8  _pad1 : 3;  /* padding */
	uint32 addr : 20;  /* physical address */
} PageTableEntry;

/* Page Directory containing 1024 PDE's */
typedef struct {
	PageDirectoryEntry entries[1024];
} PageDirectory;

/* setup kernel page directory */
void kernel_memory_pd_init();

/* get a pointer to the kernel page table */
PageDirectory *kernel_memory_pd_get();

/* setup 32bit paging */
void kernel_memory_paging_init();

#endif
