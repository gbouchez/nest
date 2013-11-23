#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

#define MULTIBOOT_MAGIC_NUMBER 0x2BADB002
#define KERNEL_MESSAGE_WELCOME "NEST Experimental System Time Alpha\n"
#define KERNEL_MESSAGE_MULTIBOOT "Kernel was loaded using multiboot "\
				 "specification.\n"

extern void kernel_main(uint32_t eax);

void check_multiboot(uint32_t eax);

#endif
