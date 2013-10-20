#include "terminal.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void)
{
	terminal_clearscreen();
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) VGA_ADDRESS;
	new_input();
}

void terminal_clearscreen(void)
{
	terminal_gotoxy(0,0);
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_gotoxy(uint8_t x, uint8_t y)
{
	terminal_row = y;
	terminal_column = x;
}

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

void terminal_putchar(char c)
{
	if (c == '\n')
	{
		line_feed();
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		terminal_newline();
	}
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

// Newline functions
void terminal_newline(void)
{
	if (++terminal_row == VGA_HEIGHT)
	{
		for (size_t y = 0; y < VGA_HEIGHT; y++)
		{
			for (size_t x = 0; x < VGA_WIDTH; x++)
			{			
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = terminal_buffer[index+VGA_WIDTH];
			}
		}
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{			
			const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
		terminal_row--;
	};
}

void line_feed(void)
{
	terminal_column = 0;
	terminal_newline();
}

// VGA colors management functions
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
