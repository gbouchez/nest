#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdint.h>
#include <stddef.h>

void (*terminal_initialize)(void);
void (*terminal_clearscreen)(void);
void (*terminal_gotoxy)(uint8_t x, uint8_t y);

// Output functions
void (*terminal_writestring)(const char* data);
void (*terminal_putchar)(char c);
void (*terminal_putentryat)(char c, size_t x, size_t y);

// Newline functions
void (*terminal_newline)(void);
void (*terminal_linefeed)(void);

// TODO Move out to shell interpreter
void new_input(void);

#endif
