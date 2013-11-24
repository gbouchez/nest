#ifndef VGA
#define VGA

#include <stddef.h>

#define TERMINAL_SET_VGA \
terminal_initialize = &vga_initialize; \
terminal_clearscreen = &vga_clearscreen; \
terminal_gotoxy = &vga_gotoxy; \
terminal_writestring = &vga_writestring; \
terminal_putchar = &vga_putchar; \
terminal_putentryat = &vga_putentryat; \
terminal_newline = &vga_newline; \
terminal_linefeed = &vga_linefeed; \

#define VGA_ADDRESS 0xB8000

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

enum vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

size_t vga_row;
size_t vga_column;
uint8_t vga_color;

uint16_t* vga_buffer;

void vga_initialize(void);
void vga_clearscreen(void);
void vga_gotoxy(uint8_t x, uint8_t y);
void vga_writestring(const char* data);
void vga_putchar(char c);
void vga_putentryat(char c, size_t x, size_t y);
void vga_linefeed(void);
void vga_newline(void);
void vga_setcolor(uint8_t color);
uint8_t vga_makecolor(enum vga_color fg, enum vga_color bg);
uint16_t vga_makeentry(char c, uint8_t color);

#endif
