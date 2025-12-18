#include "heapbanks.h"

int heap_init(Heap *heap) {
    // *memset(*ptr, value, size) Set value from ptr : ptr + size to value
    memset(heap->memory, 0, TOTAL_HEAP_SIZE);
    memset(heap->bank_allocated, 0, NUM_HEAP_BANK);
    memset(heap->bank_sizes, 0, NUM_HEAP_BANK * sizeof(uint32_t));
    return 0;
}

uint32_t bank_to_addr(int bank_index) {
    return HEAP_BANK_START + (bank_index * HEAP_BANK_SIZE);
}

int addr_to_bank(uint32_t address) {
    if (address < HEAP_BANK_START || address >= HEAP_BANK_END) {
        printf("Err: Invalid address: %u", address);
        return -1;
    }
}

int find_free_banks(Heap *heap, uint32_t num_banks) {
    if (num_banks > NUM_HEAP_BANK) {
        return -1;       // Remember to call register dump 
    }

    for (int i = 0; i <= NUM_HEAP_BANK - num_banks; i++) {
        bool all_free = true;

        // Check consecutive banks
        for (uint32_t j = 0; j < num_banks; j++) {
            if (heap->bank_allocated[i+j]) {
                all_free = false;
                break;
            }
        }

        if (all_free) return i; // Found a valid chain's starting index
    }

    return -1;          // No space available
}

uint32_t heap_malloc(Heap *heap, uint32_t num_bytes) {
    if (num_bytes == 0 || num_bytes > TOTAL_HEAP_SIZE) {
        printf("Err: %u bytes cannot fit in our heap!", num_bytes);
        return 0;   // Return 0 for failed allocations
    }

    // Find number of banks needed and round up
    uint32_t num_banks = (num_bytes + HEAP_BANK_SIZE - 1) / HEAP_BANK_SIZE;

    int start_bank = find_free_banks(heap, num_banks);
    if (start_bank == -1) {
        printf("Err: No available banks to fit %u bytes!", num_bytes);
        return 0;
    }

    // Allocate banks
    for (uint32_t i = 0; i < num_banks; i++) {
        heap->bank_allocated[start_bank + i] = true;
    }

    // Declare heapbank size
    heap->bank_sizes[start_bank] = num_banks;

    return bank_to_addr(start_bank);
}

int heap_free(Heap *heap, uint32_t address) {
    int bank_index = addr_to_bank(address);

    if (bank_index == -1) {
        printf("Err: Invalid bank address: %u", address);
        return -1;
    }

    if (!heap->bank_allocated[bank_index]) {
        printf("Err: Bank already free: %u", address);
        return -1;
    }

    uint32_t num_banks = heap->bank_sizes[bank_index];

    if (num_banks == 0) {
        printf("Err: Trying to free banks from the middle of a chain!");
        return -1;
    }

    for (uint32_t i = 0; i < num_banks; i++) {
        heap->bank_allocated[bank_index + i] = false;
    }

    heap->bank_sizes[bank_index] = 0;
    return 0;
}