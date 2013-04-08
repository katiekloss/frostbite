/*
 * Copyright (c) 2012 Katie Kloss <kloss.katherine@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stddef.h>
#include <string.h>

// XXX: This is only for debugging, not production use!
void long_to_str(unsigned long n, char *dest)
{
    char digits[11];
    digits[10] = '\0';
    int i;
    for(i = 9; i >= 0; i--)
    {
        int digit = n % 10;
        digits[i] = digit + 48;
        n = (n - digit) / 10;
        if(n == 0) break;
    }
    strncpy(dest, digits + i, 11 - i);
}

int strlen(const char *s)
{
    int i = 0;
    while(1)
    {
        if(*(s + i) == '\0') {
            return i;
        }
        i++;
    }
}

char * strncpy(char *dest, const char *src, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(*(src + i) == '\0') break;
        *(dest + i) = *(src + i);
    }
    *(dest + i) = '\0';
    return dest;
}

char * strncat(char *dest, const char *src, int n)
{
    char *start = dest;
    while(*dest != '\0') dest++;
    for(; n > 0 && *src != '\0'; n--)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return start;
}

int strncmp(const char *s1, const char *s2, int n)
{
    for(; n > 1 && *s1 == *s2 && *s1 != '\0' && *s2 != '\0'; n--)
    {
        s1++;
        s2++;
    }
    if(*s1 > *s2) return 1;
    if(*s1 < *s2) return -1;
    return 0;
}

char * strstr(const char *src, const char *sub)
{
    int sublen = strlen(sub);
    if(sublen == 0) return (char *) src;
    while(*src != '\0')
    {
        if(*src == *sub && strncmp(src, sub, sublen) == 0) return (char *) src;
        src++;
    }
    return (char *) 0;
}

void memset(void *dst, unsigned char byte, size_t n)
{
    void *i;
    for(i = dst; i < (dst + n); i++)
    {
        *((unsigned char *)i) = byte;
    }
}
