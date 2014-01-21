#include <stdint.h>
#include "kernel.h"
#include "terminal.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"

void kernel_main(uint32_t eax)
{
	gdt_install();
	idt_install();
	isrs_install();
	TERMINAL_SET_VGA
	terminal_initialize();
	terminal_writestring(KERNEL_MESSAGE_WELCOME);
	if (check_multiboot(eax) == 1) {
		terminal_writestring(KERNEL_MESSAGE_MULTIBOOT);
	}
	new_input();
	terminal_putchar(12/0);
	new_input();
	for(;;);
}

uint8_t check_multiboot(uint32_t eax)
{
        if (eax == MULTIBOOT_MAGIC_NUMBER) {
                return 1;
        }
        return 0;
}

// Thanks to Bran's kernel development tutorial
void outportb(uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
