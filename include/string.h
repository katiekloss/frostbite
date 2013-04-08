#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

void long_to_str(unsigned long n, char *dest);
int strlen(const char *s);
char * strncpy(char *dest, const char *src, int n);
char * strncat(char *dest, const char *src, int n);
int strncmp(const char *s1, const char *s2, int n);
char * strstr(const char *src, const char *sub);

void memset(void *dst, unsigned char byte, size_t n);

#endif
