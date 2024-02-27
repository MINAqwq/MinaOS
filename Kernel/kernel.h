#ifndef KERNEL_H
#define KERNEL_H

/* fatal error will atm just hlt the cpu and print text */
void kernel_error_fatal(const char *error);

#endif
