#include "terminal.h"
#include "lib/string.h"

void new_input(void)
{
	terminal_writestring("input>");
}

// Output functions
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
}
