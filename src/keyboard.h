#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isrs.h"

#define KEY_SCROLL_LOCK 128
#define KEY_NUM_LOCK 129
#define KEY_CAPS_LOCK 130

#define KEY_FLAG_SCROLL_LOCK 0x01
#define KEY_FLAG_NUM_LOCK 0x02
#define KEY_FLAG_CAPS_LOCK 0x04

#define KEY_CODES_NUMBER 128

unsigned char *kbd;
unsigned char kbdus[KEY_CODES_NUMBER];
unsigned char kbdfr[KEY_CODES_NUMBER];

void keyboard_handler(struct regs *r);
void keyboard_install(void);

#endif
