#include <stdarg.h>
#include "keyboard.h"
#include "isrs.h"
#include "irq.h"
#include "terminal.h"
#include "kernel.h"

uint8_t keyboard_flags = 0;

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[KEY_CODES_NUMBER] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   KEY_LEFT_SHIFT,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   KEY_RIGHT_SHIFT,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    KEY_CAPS_LOCK,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    KEY_NUM_LOCK,	/* 69 - Num lock*/
    KEY_SCROLL_LOCK,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdfr[KEY_CODES_NUMBER] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'a', 'z', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',	/* 39 */
 '\'', '`',   KEY_LEFT_SHIFT,		/* Left shift */
 '\\', 'w', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  ',', ';', ':', '!',   KEY_RIGHT_SHIFT,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    KEY_CAPS_LOCK,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    KEY_NUM_LOCK,	/* 69 - Num lock*/
    KEY_SCROLL_LOCK,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
    	if (kbd[scancode] == KEY_LEFT_SHIFT || kbd[scancode] == KEY_RIGHT_SHIFT)
    	{
    		keyboard_flags &= ~KEY_FLAG_SHIFT;
    		return;
    	}
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
    	if (kbd[scancode] == KEY_LEFT_SHIFT || kbd[scancode] == KEY_RIGHT_SHIFT)
    	{
    		keyboard_flags |= KEY_FLAG_SHIFT;
    		return;
    	}
    	
        if (kbd[scancode] == KEY_CAPS_LOCK
	|| kbd[scancode] == KEY_NUM_LOCK
	|| kbd[scancode] == KEY_SCROLL_LOCK) {
		switch (kbd[scancode]) {
			case KEY_CAPS_LOCK:
			keyboard_flags ^= KEY_FLAG_CAPS_LOCK;
				break;
			case KEY_NUM_LOCK:
			keyboard_flags ^= KEY_FLAG_NUM_LOCK;
				break;
			case KEY_SCROLL_LOCK:
			keyboard_flags ^= KEY_FLAG_SCROLL_LOCK;
			break;
		}
        	while((inportb(KEYBOARD_CONTROL_REGISTER) & 2) != 0);
        	outportb(KEYBOARD_DATA_REGISTER, 0xED);
        	inportb(KEYBOARD_DATA_REGISTER);
        	while((inportb(KEYBOARD_CONTROL_REGISTER) & 2) != 0);
        	outportb(KEYBOARD_DATA_REGISTER, keyboard_flags & 0x7);
        } else {
        	char display = kbd[scancode];
        	if (display >= 'a' && display <= 'z'
        	&& (
        		(keyboard_flags & (KEY_FLAG_SHIFT | KEY_FLAG_CAPS_LOCK)) != 0
        		&& (keyboard_flags & (KEY_FLAG_SHIFT | KEY_FLAG_CAPS_LOCK)) != (KEY_FLAG_SHIFT | KEY_FLAG_CAPS_LOCK)
        	))
        	{
        		display -= 32;
        	}
	        terminal_putchar(display);
	    }
    }
}

void keyboard_install(void)
{
	kbd = kbdus;
	irq_install_handler(1, keyboard_handler);
}
