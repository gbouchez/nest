#include <stdint.h>
#include "kernel.h"
#include "terminal.h"

void kernel_main(uint32_t eax)
{
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
