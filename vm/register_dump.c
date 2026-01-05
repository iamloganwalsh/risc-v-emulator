#include "register_dump.h"
#include <stdio.h>

void register_dump(uint32_t instruction, VM *vm) {
    printf("Illegal Operation: 0x%08x\n", instruction);
    register_dump_silent(vm);
}

void register_dump_silent(VM *vm) {
    for (int i = 0; i < NUM_REGISTER; i++) {
        printf("R[%d] = 0x%08x\n", i, vm->regs[i]);
    }
}