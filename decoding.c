#include "decoding.h"
#include <stdio.h>

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

int type_i(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint32_t unsigned_imm = (instruction >> 20) & 0xFFF;
    int32_t signed_mm = (int32_t)instruction >> 20;     // Sign extended SIGNED integer
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;   // 5 bits
    uint8_t func3 = (instruction & 0x00007000) >> 12;   // 3 bits
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits
    
    switch (opcode) {
        case 0b0010011:
            switch (func3){
                case 0b000:
                    // addi (2)
                    break;

                case 0b010:
                    // slti (23)
                    break;

                case 0b011:
                    // sltiu (25)

                case 0b100:
                    //xori (6)
                    break;

                case 0b110:
                    // ori (8)
                    break;

                case 0b111:
                    // andi (10)
                    break;
            }

        case 0000011:
            switch(func3) {
                case 0b000:
                    // lb (14)
                    break;

                case: 0b001:
                    // lh (15)
                    break;

                case: 0b010:
                    // lw (16)
                    break;

                case 0b100:
                    // lbu (17)
                    break;

                case 0b101:
                    // lhu (18)
                    break;
            }

        case 0b1100111:
            switch (func3) {
                case 0b000:
                    // jalr (33)
                    break;
            }
    }
    return 0;
}

int type_s(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint8_t rs2   = (instruction & 0x01F00000) >> 20; // 5 bits
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;   // 5 bits
    uint8_t func3 = (instruction & 0x00007000) >> 12;   // 3 bits
    uint32_t unsigned_imm = 
        ((instruction >> 7) & 0x1F) |
        (((instruction >> 25) & 0x7F) << 5);
    int32_t signed_imm = ((int32_t)(unsigned_imm << 20)) >> 20;     // Replace trailing/leading (non-important 32-bit bits) with sign extension (based on unsigned_imm)
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits

    switch (opcode) {
        case: 0b0100011:
            switch (func3) {
                case: 0b000:
                    // sb (19)
                    break;

                case: 0b001:
                    // sh (20)
                    break;

                case 0b010:
                    // sw (21)
                    break;
            }
    }
    return 0;
}

int type_sb(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint8_t rs2   = (instruction & 0x01F00000) >> 20; // 5 bits
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;   // 5 bits
    uint8_t func3 = (instruction & 0x00007000) >> 12;   // 3 bits
    uint32_t unsigned_imm = 
        ((instruction >> 7) & 0x1) << 11 |
        ((instruction >> 8) & 0xF) << 1 |   // Shift by 1 to create that 0th bit (which will be 0, needed bc branching shifts right and drops this bit)
        ((instruction >> 25) & 0x3F) << 5 |
        ((instruction >> 31) & 0x1) << 12;
    int32_t signed_imm = ((int32_t)(unsigned_imm << 19)) >> 19;     // Shift by 19 to reserve that 0 bit
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits

    switch (func3){
        case 0b000:
            // beq (26)
            break;

        case 0b001:
            // bne (27)
            break;

        case 0b100:
            // blt (28)
            break;

        case 0b101:
            // bge (30)
            break;

        case 0b110:
            // bltu (29)
            break;
        
        case 0b111:
            // bgeu (31)
            break;
    }

    return 0;
}

int type_u(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint32_t unsigned_imm = ((instruction >> 12) & 0xFFFFF) << 12;
    int32_t signed_imm = (int32_t)unsigned_imm;         // We don't bit shift this one, we want 11:0 = 0
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits

    // lui (4)
    return 0;
}

int type_uj(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint32_t unsigned_imm = 
        ((instruction >> 12) & 0xFF) << 12 | 
        ((instruction >> 20) & 0x1) << 11 |
        ((instruction >> 21) & 0x3FF) << 1 |
        ((instruction >> 31) & 0x1) << 20;
    int32_t signed_imm = ((int32_t)(unsigned_imm << 11)) >> 11;     // Shift by 11 to preserve a 0th bit = 0
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits

    // jal (32)
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