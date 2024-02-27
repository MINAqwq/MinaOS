#include "../kernel.h"
#include "../video/video.h"
#include "internal.h"

void
kernel_int_handle(KernelIntStack *stack)
{
	switch (stack->interrupt) {
		/* TODO: Error handling with cool debug hlt screen */
	case INT_FAUL_DE:
		kernel_error_fatal("Divide by 0\n");
		break;
	case INT_FAUL_DB:
	case INT_INTR_NI:
	case INT_TRAP_BP:
	case INT_TRAP_OF:
	case INT_FAUL_BR:
	case INT_FAUL_UD:
	case INT_FAUL_NM:
	case INT_FAUL_DF:
	case INT_FAUL_TS:
	case INT_FAUL_NP:
	case INT_FAUL_SS:
	case INT_FAUL_GP:
	case INT_FAUL_PF:
	case INT_FAUL_MF:
	case INT_FAUL_AC:
	case INT_ABRT_MC:
	case INT_FAUL_XM:
	case INT_FAUL_VE:
	case INT_FAUL_CP:
		break;

	case INT_INTR_PTI:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_KBD:
		kernel_video_print("KBD\n");
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_CSC:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_CO1:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_CO2:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_LP2:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_FLD:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_LP1:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_RTC:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_PH0:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_PH1:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_PH2:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_PS2:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_FPU:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_PAT:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_SAT:
		kernel_int_pic_eoi(stack->interrupt - INT_PIC_REMAP);
		break;

	case INT_INTR_SYS:
		kernel_video_print("SYSCALL\n");
		break;

	default:
		break;
	}
}
