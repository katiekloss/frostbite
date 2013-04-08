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
#include <string.h>

char console[25][80];

void init_console(void)
{
    int i;
    for(i = 0; i < 25; i++)
    {
        strncpy(console[i], "", 0);
    }
    redraw_console();
}

void redraw_console(void)
{
    int i, j;
    unsigned char *vram = (unsigned char *) 0xB8000;

    for(i = 0; i < 25; i++)
    {
        int finished_line = 0;
        for(j = 0; j < 80; j++)
        {
            if(console[i][j] == '\0') finished_line = 1;

            *vram = finished_line ? ' ' : console[i][j];
            vram++;
            *vram = 0x07;
            vram++;
        }
    }
}

void printk(char *message)
{
    int last_line;

    if(strlen(console[24]) > 0)
    {
        int i;
        for(i = 0; i < 24; i++)
        {
            strncpy(console[i], console[i+1], 80);
        }
        strncpy(console[24], "", 0);
    }

    for(last_line = 0; strlen(console[last_line]) > 0 && last_line < 25; last_line++);

    strncpy(console[last_line], message, 80);

    redraw_console();
}
