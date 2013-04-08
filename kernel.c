/*
 * Copyright (c) 2013 Katie Kloss <ajk108@case.edu>
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

#include <console.h>
#include <multiboot.h>
#include <string.h>

void kinit(multiboot_info_t *multiboot_info, unsigned int magic)
{
    if (magic != 0x2BADB002)
    {
        // Boot was not performed correctly
    }

    init_console();

    // Put the string "needle" somewhere in memory
    void *needle = 4096;
    strncpy(needle, "needle", 6);

    // The start of upper memory
    void *haystack = 1024;

    // We know where it is, but still.
    while(haystack < 6000)
    {
        if(!strncmp(haystack, "needle", 6))
        {
            printk("Found it!");
            break;
        }
        haystack++;
    }
}
