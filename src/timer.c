#include "timer.h"
#include "isrs.h"
#include "irq.h"
#include "terminal.h"

uint32_t timer_ticks = 0;

void timer_handler(struct regs *r)
{
	timer_ticks++;
}

void timer_install(void)
{
	irq_install_handler(0, timer_handler);
}
