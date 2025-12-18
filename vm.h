// Contains Global definitions and struct types for HeapBanks and the VM itself
#ifndef VM_H    // Ensures file is only included once: if not defined VM_H
#define VM_H
#include <stdint.h>
#include <stdbool.h>

#define INST_MEM_START 0x0000
#define INST_MEM_END 0x03ff
#define DATA_MEM_START 0x0400
#define DATA_MEM_END 0x07ff
#define VIRTUAL_ROUTINE_START 0x0800
#define VIRTUAL_ROUTINE_END 0x08ff
#define HEAP_BANK_START 0xb700
#define HEAP_BANK_END 0xd700

#define NUM_HEAP_BANK 128
#define NUM_REGISTER 32
#define HEAP_BANK_SIZE 64
#define INST_MEM_SIZE 1024
#define DATA_MEM_SIZE 1024
#define FILE_SIZE 2048

typedef struct {
    uint32_t size;
    uint8_t data[HEAP_BANK_SIZE];
    bool is_allocated;
} HeapBank;

typedef struct {
    uint32_t pc;
    uint32_t regs[NUM_REGISTER];
    uint8_t instruction_mem[INST_MEM_SIZE];
    uint8_t data_mem[DATA_MEM_SIZE];
    HeapBank heap_banks[NUM_HEAP_BANK];
} VM;

#endif