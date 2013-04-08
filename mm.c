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

#include <mm.h>
#include <console.h>
#include <string.h>
#include <stddef.h>

#define KERN_MEMORY 2 * 1024 * 1024
#define KERN_CHUNK_SIZE 128
#define KERN_CHUNKS (KERN_MEMORY / KERN_CHUNK_SIZE)

unsigned long kmem_size;
void *kmem_start;
mm_chunk_t *chunk_list;

void init_mm(unsigned long upper_mem_size)
{
    unsigned long chunk_list_size;
    char mem_size_str[11];
    int i;

   /*
    * Preallocate a smallish amount of memory for our chunk list. 
    * Let's say (for now) that the kernel gets 2 megabytes
    * and we use 128-byte chunks (ick.)
    */
    chunk_list_size = (KERN_MEMORY / KERN_CHUNK_SIZE) * sizeof(mm_chunk_t);
    chunk_list = (mm_chunk_t *) 1024; // Upper memory starts at address 1024
    memset(chunk_list, 0, chunk_list_size);

    kmem_size = upper_mem_size;
    kmem_start = (void *) 1024 + chunk_list_size;

    // Set up each chunk with a pointer to its start
    for(i = 0; i < KERN_CHUNKS; i++)
    {
        chunk_list[i].start = (void *) kmem_start + i * KERN_CHUNK_SIZE;
    }

    printk("Initialized memory manager with");
    if(kmem_size > 1024)
    {
        long_to_str(kmem_size / 1024, mem_size_str);
        printk(mem_size_str);
        printk("megabytes of memory");
    } else {
        long_to_str(kmem_size, mem_size_str);
        printk(mem_size_str);
        printk("kilobytes of memory");
    }
}

void * kmalloc(size_t bytes)
{
    // Walk over the list of chunks until we find a set of free
    // adjacent chunks that fits the request
    int i, j, required_chunks;

    required_chunks = bytes / KERN_CHUNK_SIZE;
    if(required_chunks * KERN_CHUNK_SIZE < bytes) required_chunks++;

    for(i = 0; i < KERN_CHUNKS;)
    {
        if(chunk_list[i].flags & CHUNK_FLAGS_IN_USE) i++;
        else
        {
            for(j = 1; j < required_chunks && i + j < KERN_CHUNKS; j++)
            {
                if(chunk_list[i + j].flags & CHUNK_FLAGS_IN_USE) break;
            }
    
            if(j == required_chunks) break;
            else i += j;
        }   
    }
    if(i == KERN_CHUNKS)
    {
        return (void *) 0; // Out of memory!
    }
    
    for(j = 0; j < required_chunks; j++)
    {
        chunk_list[i + j].flags |= CHUNK_FLAGS_IN_USE;
        if(j > 0) chunk_list[i + j - 1].next = &chunk_list[i + j];
    }

    return (void *) chunk_list[i].start;
}

void kfree(void *ptr)
{
    // Free the chunk at ptr
    int i;
    for(i = 0; i < KERN_CHUNKS; i++)
    {
        if(chunk_list[i].start == ptr) break;
    }

    do
    {
        chunk_list[i].flags ^= CHUNK_FLAGS_IN_USE;
        chunk_list[i].next = 0;
        i++;
    }
    while(chunk_list[i].next != 0);
}
