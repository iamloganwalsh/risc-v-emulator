// Prints out all the registers
#ifndef REGISTER_DUMP_H
#define REGISTER_DUMP_H
#include "vm.h"

void register_dump(uint32_t instruction, VM *vm);
void register_dump_silent(VM *vm);

#endif