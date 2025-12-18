// Defines all of the operation functions
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "vm.h"

// Arithmetic
int add_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int addi_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int sub_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int lui_inst(uint8_t rd, int32_t signed_imm, VM *vm);
int xor_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int xori_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int or_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int ori_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int and_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int andi_inst(uint8_t rd, uint8_t rs1, int32_t signed_integer, VM *vm);
int sll_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int srl_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int sra_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);

// Memory access
int lb_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int lh_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int lw_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int lbu_inst(uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int lhu_inst(uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int sb_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int sh_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int sw_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);

// Program flow
int slt_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int slti_inst(uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int sltu_inst(uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int sltiu_inst(uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int beq_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int bne_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int blt_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int bltu_inst(uint8_t rs1, uint8_t rs2, uint32_t unsigned_imm, VM *vm);
int bge_inst(uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int bgeu_inst(uint8_t rs1, uint8_t rs2, uint32_t unsigned_imm, VM *vm);
int jal_inst(uint8_t rd, int32_t signed_imm, VM *vm);
int jalr_inst(uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);

#endif