#include <stdint.h>
#include "gdt.h"

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);
	
	gdt[num].granularity |= (uint8_t)(gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install(void)
{
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = (uint32_t)&gdt;
	
	// NULL descriptor
	gdt_set_gate(0,0,0,0,0);
	// Code segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	// Data segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	
	gdt_flush();
}
