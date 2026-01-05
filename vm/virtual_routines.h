// Checks virtual routine requests, matches the address to eachfunctionality
#ifndef VIRTUAL_ROUTINES_H
#define VIRTUAL_ROUTINES_H
#include "vm.h"
#include "register_dump.h"
#include "heapbanks.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int check_vr(uint32_t instruction, uint32_t memory_address, uint32_t *value, VM *vm);



#endif