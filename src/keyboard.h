#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isrs.h"

#define KEYBOARD_DATA_REGISTER 0x60
#define KEYBOARD_CONTROL_REGISTER 0x64

#define KEY_SCROLL_LOCK 128
#define KEY_NUM_LOCK 129
#define KEY_CAPS_LOCK 130

#define KEY_FLAG_SCROLL_LOCK 0x01
#define KEY_FLAG_NUM_LOCK 0x02
#define KEY_FLAG_CAPS_LOCK 0x04

#define KEY_CODES_NUMBER 128

#define KEYBOARD_COMMAND_SET_LED 0xED
#define KEYBOARD_COMMAND_ECHO 0xEE
#define KEYBOARD_COMMAND_SCAN_CODE_SET 0xF0
#define KEYBOARD_COMMAND_IDENTIFY 0xF2
#define KEYBOARD_COMMAND_TYPEMATIC 0xF3
#define KEYBOARD_COMMAND_ENABLE_SCANNING 0xF4
#define KEYBOARD_COMMAND_DISABLE_SCANNING 0xF5
#define KEYBOARD_COMMAND_SET_DEFAULT_PARAMETERS 0xF6
#define KEYBOARD_COMMAND_RESEND_LAST_BYTE 0xFE
#define KEYBOARD_COMMAND_RESET 0xFF

#define KEYBOARD_BYTE_ERROR_1 0x00
#define KEYBOARD_BYTE_SELF_TEST_PASSED 0xAA
#define KEYBOARD_BYTE_ECHO 0xEE
#define KEYBOARD_BYTE_ACK 0xFA
#define KEYBOARD_BYTE_SELF_TEST_FAILED_1 0xFC
#define KEYBOARD_BYTE_SELF_TEST_FAILED_2 0xFD
#define KEYBOARD_BYTE_RESEND 0xFE
#define KEYBOARD_BYTE_ERROR_2 0xFF

unsigned char *kbd;
unsigned char kbdus[KEY_CODES_NUMBER];
unsigned char kbdfr[KEY_CODES_NUMBER];

void keyboard_handler(struct regs *r);
void keyboard_install(void);

#endif
