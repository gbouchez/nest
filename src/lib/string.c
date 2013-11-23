#include <stddef.h>
#include "string.h"

void *memcpy(void *str1, const void *str2, size_t n)
{
	char* dest1 = (char*)str1;
	char* dest2 = (char*)str2;
        while (n--)
                *dest1++ = *dest2++;
	return str1;
}

size_t strlen(const char* str)
{
	size_t i = 0;
	while(str[i] != 0)
		i++;
	return i;
}
