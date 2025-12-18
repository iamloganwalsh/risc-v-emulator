#include "decoding.h"

int type_r(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint8_t func7 = (instruction & 0xFE000000) >> 25; // 7 bits
    uint8_t rs2   = (instruction & 0x01F00000) >> 20; // 5 bits
    uint8_t rs1   = (instruction & 0x000F8000) >> 15; // 5 bits
    uint8_t func3 = (instruction & 0x00007000) >> 12; // 3 bits
    uint8_t rd    = (instruction & 0x00000F80) >> 7;  // 5 bits

    switch (func7) {
        case 0b0000000:
            switch (func3) {
                case 0b000:
                    // add (1)
                    break;

                case 0b001:
                    // sll
                    break;

                case 0b010:
                    // slt
                    break;

                case 0b011:
                    // sltu
                    break;
                
                case 0b100:
                    // xor
                    break;

                case 0b101:
                    // srl
                    break;

                case 0b110:
                    // or
                    break;

                case 0b111:
                    // and (9)
            }

        case 0b0100000:
            switch (func3) {
                case 0b000:
                    // sub
                    break;

                case 0b101:
                    // sra
                    break;
            }
    }

    return 0;
}

int process_instruction(uint32_t instruction, VM *vm) {
    // Opcode contained in the last 7 bits so we can make to retrieve these
    uint8_t bitmask = 0x7F;
    uint8_t opcode = instruction & bitmask;

    switch (opcode) {
        case 0b0110011:
            type_r(instruction, opcode, vm);
            break;
        
        // case 0b0010011:
        //     type_i(instruction, opcode, vm);
        //     break;
            
        // case 0b0110111:
        //     type_u(instruction, opcode, vm);
        //     break;

        // case 0b0000011:
        //     type_i(instruction, opcode, vm);
        //     break;

        // case 0b0100011:
        //     type_s(instruction, opcode, vm);
        //     break;
        
        // case 0b1100011:
        //     type_sb(instruction, opcode, vm);
        //     break;

        // case 0b1101111:
        //     type_uj(instruction, opcode, vm);
        //     break;

        // case 0b1100111:
        //     type_i(instruction, opcode, vm);
        //     break;
    }

    return 0;
}