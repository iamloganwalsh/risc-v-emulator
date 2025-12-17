#include <stdio.h>
#include "vm.h"
#include "initialisation.h"

int main(int argc, char *argv[]) {
    VM vm = {0};        // Initialise with 0 values

    // if (argc != 2) {
    //     fprintf(stderr, "Please ensure to only pass the filename, e.g ./vm <path_to_binary_file>\n");
    //     return 1;
    // }
    // const char *filename = argv[1];
    const char *filename = "add_2_numbers.mi"
    read_file(filename, vm.instruction_mem, vm.data_mem);
    for (int i = 0; i < 4; i++) {
        printf("instr[%d] = 0x%02x\n", i, vm.instruction_mem[i]);
    }

    return 0;
}