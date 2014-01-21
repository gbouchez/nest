#ifndef TIMER_H
#define TIMER_H

#include "isrs.h"

void timer_handler(struct regs *r);
void timer_install(void);

#endif
