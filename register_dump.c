#include "register_dump.h"
#include <stdio.h>

void register_dump(uint32_t instruction, VM *vm) {
    printf("Illegal Operation: 0x%08x\n", instruction);
    for (int i = 0; i < NUM_REGISTER; i++) {
        printf("R[%d] = 0x08x\n", i, vm->regs[i]);
    }
}