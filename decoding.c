#include "decoding.h"
#include "instructions.h"
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
                    add_inst(rd, rs1, rs2, vm);
                    break;

                case 0b001:
                    sll_inst(rd, rs1, rs2, vm);
                    break;

                case 0b010:
                    slt_inst(rd, rs1, rs2, vm);
                    break;

                case 0b011:
                    sltu_inst(rd, rs1, rs2, vm);
                    break;
                
                case 0b100:
                    xor_inst(rd, rs1, rs2, vm);
                    break;

                case 0b101:
                    srl_inst(rd, rs1, rs2, vm);
                    break;

                case 0b110:
                    or_inst(rd, rs1, rs2, vm);
                    break;

                case 0b111:
                    and_inst(rd, rs1, rs2, vm);
            }

        case 0b0100000:
            switch (func3) {
                case 0b000:
                    sub_inst(rd, rs1, rs2, vm);
                    break;

                case 0b101:
                    sra_inst(rd, rs1, rs2, vm);
                    break;
            }
    }

    return 0;
}

int type_i(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint32_t unsigned_imm = (instruction >> 20) & 0xFFF;
    int32_t signed_imm = (int32_t)instruction >> 20;     // Sign extended SIGNED integer
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;   // 5 bits
    uint8_t func3 = (instruction & 0x00007000) >> 12;   // 3 bits
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits
    
    switch (opcode) {
        case 0b0010011:
            switch (func3){
                case 0b000:
                    addi_inst(rd, rs1, signed_imm, vm);
                    break;

                case 0b010:
                    slti_inst(rd, rs1, unsigned_imm, vm);
                    break;

                case 0b011:
                    sltiu_inst(rd, rs1, unsigned_imm, vm);
                    break;

                case 0b100:
                    xori_inst(rd, rs1, signed_imm, vm);
                    break;

                case 0b110:
                    ori_inst(rd, rs1, signed_imm, vm);
                    break;

                case 0b111:
                    andi_inst(rd, rs1, signed_imm, vm);
                    break;
            }

        case 0000011:
            switch(func3) {
                case 0b000:
                    lb_inst(rd, rs1, signed_imm, vm);
                    break;

                case 0b001:
                    lh_inst(rd, rs1, signed_imm, vm);
                    break;

                case 0b010:
                    lw_inst(rd, rs1, signed_imm, vm);
                    break;

                case 0b100:
                    lbu_inst(rd, rs1, unsigned_imm, vm);
                    break;

                case 0b101:
                    lhu_inst(rd, rs1, unsigned_imm, vm);
                    break;
            }

        case 0b1100111:
            switch (func3) {
                case 0b000:
                    jalr_inst(rd, rs1, signed_imm, vm);
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
        case 0b0100011:
            switch (func3) {
                case 0b000:
                    sb_inst(rs1, rs2, signed_imm, vm);
                    break;

                case 0b001:
                    sh_inst(rs1, rs2, signed_imm, vm);
                    break;

                case 0b010:
                    sw_inst(rs1, rs2, signed_imm, vm);
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
            beq_inst(rs1, rs2, signed_imm, vm);
            break;

        case 0b001:
            bne_inst(rs1, rs2, signed_imm,  vm);
            break;

        case 0b100:
            blt_inst(rs1, rs2, signed_imm, vm);
            break;

        case 0b101:
            bge_inst(rs1, rs2, signed_imm, vm);
            break;

        case 0b110:
            bltu_inst(rs1, rs2, unsigned_imm, vm);
            break;
        
        case 0b111:
            bgeu_inst(rs1, rs2, unsigned_imm, vm);
            break;
    }

    return 0;
}

int type_u(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint32_t unsigned_imm = ((instruction >> 12) & 0xFFFFF) << 12;
    int32_t signed_imm = (int32_t)unsigned_imm;         // We don't bit shift this one, we want 11:0 = 0
    uint8_t rd    = (instruction & 0x00000F80) >> 7;    // 5 bits

    lui_inst(rd, signed_imm, vm);
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

    jal_inst(rd, signed_imm, vm);
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