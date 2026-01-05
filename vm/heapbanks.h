#ifndef HEAPBANKS_H
#define HEAPBANKS_H

#include <string.h>
#include "vm.h"
#include <stdio.h>

int heap_init(Heap *heap);
uint32_t bank_to_addr(int bank_index);
int find_free_banks(Heap *heap, uint32_t num_banks);
uint32_t heap_malloc(Heap *heap, uint32_t num_bytes);
int heap_free(Heap *heap, uint32_t address);

#endif