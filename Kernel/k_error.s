.global kernel_error_fatal

.type kernel_error_fatal, @function
kernel_error_fatal:
    hlt
    ret
