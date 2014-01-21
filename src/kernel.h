#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

#define MULTIBOOT_MAGIC_NUMBER 0x2BADB002
#define KERNEL_MESSAGE_WELCOME "NEST Experimental System Time Alpha\n"
#define KERNEL_MESSAGE_MULTIBOOT "Kernel was loaded using multiboot "\
				 "specification.\n"

extern void kernel_main(uint32_t eax);

uint8_t check_multiboot(uint32_t eax);

extern void outportb(uint16_t _port, uint8_t _data);
extern unsigned char inportb (uint16_t _port);

#endif
