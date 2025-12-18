#include "virtual_routines.h"
#include "limits.h"

int check_vr(uint32_t instruction, uint32_t memory_address, uint32_t *value, VM *vm) {
    uint32_t value_copy = *value;

    if (memory_address == 0x0800) {
        char ascii_char = (char)value_copy;
        printf("%c", ascii_char);
        return 1;
    }

    else if (memory_address == 0x0804) {
        int32_t signed_value = (int32_t)value_copy;
        printf("%d", signed_value);
        return 1;
    }

    else if (memory_address == 0x0808) {
        printf("%d", value_copy);
    }

    else if (memory_address == 0x080C) {
        print("CPU Halt Requested");
        exit(1);
    }

    else if (memory_address == 0x0812) {
        char input;

        if (scanf("%c", &input) != 1) {
            printf("Error reading input\n");
            exit(1);
        }

        if (input >= 0 && input <= 127) {
            uint32_t val = (uint32_t)input; // Cast ASCII character to uint32t
            *value = val;
        } else {
            register_dump(vm);
            exit(1);
        }
        return 0;
    }

    else if (memory_address == 0x0816) {
        int32_t input;
        if (scanf("%d", &input) != 1) {
            printf("Error reading input\n");
            exit(1);
        }

        if (input > INT_MAX || input < INT_MIN) {
            register_dump(vm);
            exit(1);
        }

        *value = input;
    }
    
    else if (memory_address == 0x0820) {
        printf("%x", vm->pc);
    }

    else if (memory_address == 0x0824) {
        register_dump_silent(vm);
    }

    else if (memory_address == 0x0828) {
        
    }
}
