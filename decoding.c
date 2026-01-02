#include "decoding.h"
#include "instructions.h"
#include <stdio.h>

int type_r(uint32_t instruction, VM *vm) {
    uint8_t func7 = (instruction & 0xFE000000) >> 25;
    uint8_t rs2   = (instruction & 0x01F00000) >> 20;
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;
    uint8_t func3 = (instruction & 0x00007000) >> 12;
    uint8_t rd    = (instruction & 0x00000F80) >> 7;

    switch (func7) {
        case 0b0000000:
            switch (func3) {
                case 0b000:
                    add_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b001:
                    sll_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b010:
                    slt_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b011:
                    sltu_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b100:
                    xor_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b101:
                    srl_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b110:
                    or_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b111:
                    and_inst(instruction, rd, rs1, rs2, vm);
                    break;
            }
            break;

        case 0b0100000:
            switch (func3) {
                case 0b000:
                    sub_inst(instruction, rd, rs1, rs2, vm);
                    break;
                case 0b101:
                    sra_inst(instruction, rd, rs1, rs2, vm);
                    break;
            }
            break;
    }

    return 0;
}

int type_i(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint32_t unsigned_imm = (instruction >> 20) & 0xFFF;
    int32_t signed_imm = (int32_t)instruction >> 20;
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;
    uint8_t func3 = (instruction & 0x00007000) >> 12;
    uint8_t rd    = (instruction & 0x00000F80) >> 7;
    
    switch (opcode) {
        case 0b0010011:
            switch (func3){
                case 0b000:
                    addi_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b010:
                    slti_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b011:
                    sltiu_inst(instruction, rd, rs1, unsigned_imm, vm);
                    break;
                case 0b100:
                    xori_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b110:
                    ori_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b111:
                    andi_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
            }
            break;

        case 0b0000011:
            switch(func3) {
                case 0b000:
                    lb_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b001:
                    lh_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b010:
                    lw_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
                case 0b100:
                    lbu_inst(instruction, rd, rs1, unsigned_imm, vm);
                    break;
                case 0b101:
                    lhu_inst(instruction, rd, rs1, unsigned_imm, vm);
                    break;
            }
            break;

        case 0b1100111:
            switch (func3) {
                case 0b000:
                    jalr_inst(instruction, rd, rs1, signed_imm, vm);
                    break;
            }
            break;
    }
    return 0;
}

int type_s(uint32_t instruction, uint8_t opcode, VM *vm) {
    uint8_t rs2   = (instruction & 0x01F00000) >> 20;
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;
    uint8_t func3 = (instruction & 0x00007000) >> 12;
    uint32_t unsigned_imm = 
        ((instruction >> 7) & 0x1F) |
        (((instruction >> 25) & 0x7F) << 5);
    int32_t signed_imm = ((int32_t)(unsigned_imm << 20)) >> 20;

    switch (opcode) {
        case 0b0100011:
            switch (func3) {
                case 0b000:
                    sb_inst(instruction, rs1, rs2, signed_imm, vm);
                    break;
                case 0b001:
                    sh_inst(instruction, rs1, rs2, signed_imm, vm);
                    break;
                case 0b010:
                    sw_inst(instruction, rs1, rs2, signed_imm, vm);
                    break;
            }
            break;
    }
    return 0;
}

int type_sb(uint32_t instruction, VM *vm) {
    uint8_t rs2   = (instruction & 0x01F00000) >> 20;
    uint8_t rs1   = (instruction & 0x000F8000) >> 15;
    uint8_t func3 = (instruction & 0x00007000) >> 12;
    uint32_t unsigned_imm = 
        ((instruction >> 7) & 0x1) << 11 |
        ((instruction >> 8) & 0xF) << 1 |
        ((instruction >> 25) & 0x3F) << 5 |
        ((instruction >> 31) & 0x1) << 12;
    int32_t signed_imm = ((int32_t)(unsigned_imm << 19)) >> 19;

    switch (func3){
        case 0b000:
            beq_inst(instruction, rs1, rs2, signed_imm, vm);
            break;
        case 0b001:
            bne_inst(instruction, rs1, rs2, signed_imm, vm);
            break;
        case 0b100:
            blt_inst(instruction, rs1, rs2, signed_imm, vm);
            break;
        case 0b101:
            bge_inst(instruction, rs1, rs2, signed_imm, vm);
            break;
        case 0b110:
            bltu_inst(instruction, rs1, rs2, signed_imm, vm);
            break;
        case 0b111:
            bgeu_inst(instruction, rs1, rs2, signed_imm, vm);
            break;
    }

    return 0;
}

int type_u(uint32_t instruction, VM *vm) {
    uint32_t unsigned_imm = ((instruction >> 12) & 0xFFFFF) << 12;
    int32_t signed_imm = (int32_t)unsigned_imm;
    uint8_t rd    = (instruction & 0x00000F80) >> 7;

    lui_inst(instruction, rd, signed_imm, vm);
    return 0;
}

int type_uj(uint32_t instruction, VM *vm) {
    uint32_t unsigned_imm = 
        ((instruction >> 12) & 0xFF) << 12 | 
        ((instruction >> 20) & 0x1) << 11 |
        ((instruction >> 21) & 0x3FF) << 1 |
        ((instruction >> 31) & 0x1) << 20;
    int32_t signed_imm = ((int32_t)(unsigned_imm << 11)) >> 11;
    uint8_t rd    = (instruction & 0x00000F80) >> 7;

    jal_inst(instruction, rd, signed_imm, vm);
    return 0;
}

int process_instruction(uint32_t instruction, VM *vm) {

    uint8_t bitmask = 0x7F;
    uint8_t opcode = instruction & bitmask;

    switch (opcode) {
        case 0b0110011:
            type_r(instruction, vm);
            break;
        case 0b0010011:
            type_i(instruction, opcode, vm);
            break;
        case 0b0110111:
            type_u(instruction, vm);
            break;
        case 0b0000011:
            type_i(instruction, opcode, vm);
            break;
        case 0b0100011:
            type_s(instruction, opcode, vm);
            break;
        case 0b1100011:
            type_sb(instruction, vm);
            break;
        case 0b1101111:
            type_uj(instruction, vm);
            break;
        case 0b1100111:
            type_i(instruction, opcode, vm);
            break;
        default:
            printf("Instruction not implemented: 0x%08x\n", instruction);
            exit(1);
    }

    return 0;
}