#include "kdebug.h"
#include "io.h"
#include "stdint.h"

void kprint_u32integer10(uint32_t num)
{
	char buffer[11] = {};
	uint8_t i = 10;
	buffer[i--] = '\0';
	if (num == 0)
	{
		buffer[i--] = '0';
	} else {
		for (;num > 0;)
		{
			buffer[i--] = '0'+(num % 10);
			num /= 10;
		}
	}
	
	output_string(&buffer[i+1]);
}


void kprint_u32integer16(uint32_t num)
{
	char buffer[11] = {'a','b','b','b','b','b','b','b','b','b','b'};
	uint8_t i = 10;
	buffer[i--] = '\0';
	if (num == 0)
	{
		buffer[i--] = '0';
		buffer[i--] = '0';
	} else {
		for (;num > 0 || i % 2 == 0;i--)
		{
			if (num == 0)
			{
				buffer[i] = '0';
			} else {
				buffer[i] = '0'+(num % 16);
				if (buffer[i] > '9')
				{
					buffer[i] = 'A' + (buffer[i] - '9') - 1;
				}
				num /= 16;
			}
		}
	}
	buffer[i--] = 'x';
	buffer[i] = '0';
	
	output_string(&buffer[i]);
}
