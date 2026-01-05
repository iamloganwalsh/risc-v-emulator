#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "initialisation.h"
#include "decoding.h"

int main(int argc, char *argv[]) {
    VM vm = {0};        // Initialise with 0 values

    if (argc != 2) {
        fprintf(stderr, "Please specify only the filepath, e.g ./vm printing_h.mi\n");
        return 1;
    }
    const char *filename = argv[1];

    if (read_file(filename, vm.instruction_mem, vm.data_mem) == 1) {
        exit(1);    // if above returns 1, there was an error parsing the file
    }

    // Next step: instruction parsing
    while (vm.pc < INST_MEM_SIZE) {
        // Fetch instruction at current PC
        uint32_t instruction = 
            vm.instruction_mem[vm.pc] |
            (vm.instruction_mem[vm.pc + 1] << 8) |
            (vm.instruction_mem[vm.pc + 2] << 16) |
            (vm.instruction_mem[vm.pc + 3] << 24);

        // Clear register 0 (always zero)
        vm.regs[0] = 0;

        // Decode and execute instruction (this will update vm.pc)
        process_instruction(instruction, &vm);
    }

    return 0;
}