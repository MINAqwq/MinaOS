/* high level kernel entry */

#include "interrupts/interrupts.h"
#include "video/video.h"

void
kernel_main()
{
	/* init vga driver */
	kernel_video_init(KERNEL_VIDEO_DEVICE_VGA);

	/* setup interrupts */
	kernel_video_print("Setup interrupts...\n");
	kernel_int_setup();
}
