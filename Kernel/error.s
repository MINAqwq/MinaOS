.global kernel_error_fatal

.data
_k_str_fatal:
.ascii "[FATAL] "

.text

.type kernel_error_fatal, @function
/* arg1: error str */
kernel_error_fatal:
    push $_k_str_fatal
    call kernel_video_print

    mov 8(%esp), %eax

    push %eax
    call kernel_video_print
    
    hlt

