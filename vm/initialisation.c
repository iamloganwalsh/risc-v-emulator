#include "initialisation.h"

    
int read_file(const char *filename, uint8_t *instruction_mem, uint8_t *data_mem){        // *data_mem allows us to work directly on these values
    FILE *fptr;
    fptr = fopen(filename, "rb");

    if (!fptr) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    unsigned char buffer[FILE_SIZE];
    size_t numBytes = fread(buffer, 1, FILE_SIZE, fptr);    // buffer, size of each element, num elements to read, file pointer
    
    if (numBytes != FILE_SIZE) {
        fprintf(stderr, "Incorrect file size\n");
        return 1;
    }

    for (int i = 0; i < INST_MEM_SIZE; i++) {
        instruction_mem[i] = buffer[i]; // Don't need to pass vm because we are directly referencing the memory in the struct
    }

    for (int i = INST_MEM_SIZE; i < INST_MEM_SIZE + DATA_MEM_SIZE; i++) {
        data_mem[i - INST_MEM_SIZE] = buffer[i];
    }
}

