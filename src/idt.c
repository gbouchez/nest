#include "lib/string.h"
#include "idt.h"
#include <stdint.h>

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}

void idt_install(void)
{
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = &idt;
	
	memset(&idt, 0, sizeof(struct idt_entry)*256);
	
	idt_load();
}
