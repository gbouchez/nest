#ifndef STDLIB_STRING_H
#define STDLIB_STRING_H

#include <stddef.h>

void *memcpy(void *str1, const  void *str2, size_t n);
void *memset(void *s, int c, size_t n);
size_t strlen(const char* str);

#endif
