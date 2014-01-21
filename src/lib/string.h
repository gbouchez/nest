#ifndef STDLIB_STRING_H
#define STDLIB_STRING_H

#include <stddef.h>

extern void *memcpy(void *str1, const  void *str2, size_t n);
extern void *memset(void *s, int c, size_t n);
extern size_t strlen(const char* str);

#endif
