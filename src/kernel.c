#include "terminal.h"

#if defined(__linux__)
#error "You need a cross-compiler."
#endif

void kernel_main()
{
	terminal_initialize();
	char test[60];
	for (int i = 0; i < 60; i = i+2)
	{
		test[i] = 48 + ((i/2)%10);
		test[i+1] = '\n';
	}
	terminal_writestring(test);
}
