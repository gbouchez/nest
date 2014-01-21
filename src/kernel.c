#include <stdint.h>
#include "kernel.h"
#include "terminal.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "keyboard.h"

#define KEYBOARD_LAYOUT_FR

void kernel_main(uint32_t eax)
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	__asm__ __volatile__ ("sti");
	timer_install();
	keyboard_install();
	#ifdef KEYBOARD_LAYOUT_FR
	kbd = kbdfr;
	#endif
	TERMINAL_SET_VGA
	terminal_initialize();
	terminal_writestring(KERNEL_MESSAGE_WELCOME);
	if (check_multiboot(eax) == 1) {
		terminal_writestring(KERNEL_MESSAGE_MULTIBOOT);
	}
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

unsigned char inportb (uint16_t _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
