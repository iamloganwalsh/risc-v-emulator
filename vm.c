#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "initialisation.h"

int main(int argc, char *argv[]) {
    VM vm = {0};        // Initialise with 0 values

    // if (argc != 2) {
    //     fprintf(stderr, "Please ensure to only pass the filename, e.g ./vm <path_to_binary_file>\n");
    //     return 1;
    // }
    // const char *filename = argv[1];
    const char *filename = "add_2_numbers.mi";

    if (read_file(filename, vm.instruction_mem, vm.data_mem) == 1) {
        exit(1);    // if above returns 1, there was an error parsing the file
    }

    // Next step: instruction parsing
for (int i = 0; i < INST_MEM_SIZE; i += 4) {
    uint32_t instr = 
        vm.instruction_mem[i] |
        (vm.instruction_mem[i+1] << 8) |
        (vm.instruction_mem[i+2] << 16) |
        (vm.instruction_mem[i+3] << 24); // little-endian encoded

    vm.regs[0] = 0; // Clear 0th register
    printf("Instruction %d: 0x%08x\n", i/4, instr);
    
    process_instruction(instruction, &vm);
}

    return 0;
}