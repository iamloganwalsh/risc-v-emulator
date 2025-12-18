#include "virtual_routines.h"

int check_vr(uint32_t instruction, uint32_t memory_address, uint32_t *value, VM *vm) {
    uint32_t value_copy = *value;

    if (memory_address == 0x0800) {
        char ascii_char = (char)value_copy;
        printf("%c", ascii_char);
        return 1;
    }

    else if (memory_address == 0x0804) {
        int32_t signed_value = (int32_t)value_copy;
        printf("%d", signed_value);
        return 1;
    }

    else if (memory_address == 0x0808) {
        printf("%x", value_copy);
        return 1;
    }

    else if (memory_address == 0x080C) {
        printf("CPU Halt Requested\n");
        register_dump(instruction, vm);
        exit(0);
    }

    else if (memory_address == 0x0812) {
        char input;

        if (scanf("%c", &input) != 1) {
            printf("Error reading input\n");
            register_dump(instruction, vm);
            exit(1);
        }

        if (input >= 0 && input <= 127) {
            uint32_t val = (uint32_t)input; // Cast ASCII character to uint32t
            *value = val;
        } else {
            register_dump(instruction, vm);
            exit(1);
        }
        return 0;
    }

    else if (memory_address == 0x0816) {
        int32_t input;
        if (scanf("%d", &input) != 1) {
            register_dump(instruction, vm);
            exit(1);
        }

        // Size checks should be handled by int32_t
        *value = (uint32_t)input;
        return 0;
    }
    
    else if (memory_address == 0x0820) {
        printf("%08x\n", vm->pc);
        return 1;
    }

    else if (memory_address == 0x0824) {
        register_dump_silent(vm);
        return 1;
    }

    else if (memory_address == 0x0828) {
        uint32_t address = value_copy;

        // Find where this address is located

        if (address >= HEAP_BANK_START && address <= HEAP_BANK_END) {       // Heap memory
            uint32_t mem_value = *(uint32_t*)(&vm->heapbank.memory[address - HEAP_BANK_START]);  // Accessing the value at the specific heap address, can use for read or write
            printf("%08x\n", mem_value);
        }
        else if (address >= DATA_MEM_START && address <= DATA_MEM_END) {    // Data memory
            uint32_t mem_value = *(uint32_t*)(&vm->data_mem[address - INST_MEM_SIZE]);
            printf("%08x\n", mem_value);
        }
        else if (address <= INST_MEM_END) {                                  // Instruction memory
            uint32_t mem_value = *(uint32_t*)(&vm->instruction_mem[address]);
            printf("%08x\n", mem_value);
        }
        else {
            register_dump(instruction, vm);
            exit(1);
        }
        return 1;
    }

    else if (memory_address == 0x0830) {    // Heap Malloc
        uint32_t size = value_copy;
        uint32_t allocated_addr = heap_malloc(&vm->heapbank, size); // Errors return 0 so failed allocations don't need special handling
        vm->regs[28] = allocated_addr;
        return 1;
    }

    else if (memory_address == 0x0830) {
        uint32_t address = value_copy;
        int result = heap_free(&vm->heapbank, address);

        if (result != 0) {
            // heap_free failed
            register_dump(instruction, vm);
            exit(1);
        }
        return 1;
    }

    return -1;  // Not a valid routine
}
