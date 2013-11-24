#include <stdint.h>
#include "kernel.h"
#include "terminal.h"
#include "vga.h"

void kernel_main(uint32_t eax)
{
	TERMINAL_SET_VGA
	terminal_initialize();
	terminal_writestring(KERNEL_MESSAGE_WELCOME);
	check_multiboot(eax);
	new_input();
}

void check_multiboot(uint32_t eax)
{
        if (eax == MULTIBOOT_MAGIC_NUMBER) {
                terminal_writestring(KERNEL_MESSAGE_MULTIBOOT);
        }
}
