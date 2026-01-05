// Processes each instruction one by one
#ifndef DECODING_H
#define DECODING_H
#include "vm.h"
#include "instructions.h"
#include <stdint.h>
#include <stdlib.h>

int process_instruction(uint32_t instruction, VM *vm);

#endif