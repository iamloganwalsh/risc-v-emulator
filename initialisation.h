// Initialises the project, loading memory and initialising heap banks

// loading memory:
// Open the file, read the file into a buffer, check some edge cases like incorrect sizing
// load the buffer into the vm instruction memory, and load the data memory aswell

// heap banks:
// Create each heap bank using the struct and a for loop

#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "vm.h"
#include <stdio.h>

int read_file(const char *filename, uint8_t *instruction_mem, uint8_t *data_mem);


#endif