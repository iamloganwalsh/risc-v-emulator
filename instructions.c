#include "instructions.h"
#include "vm.h"
#include "register_dump.h"

// Arithmetic
int add_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] + vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int addi_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] + signed_imm;
    vm->pc += 4;
    return 0;
}

int sub_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] - vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int lui_inst(uint32_t instruction, uint8_t rd, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = signed_imm;
    vm->pc += 4;
    return 0;
}

int xor_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] ^ vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int xori_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] ^ signed_imm;
    vm->pc += 4;
    return 0;
}

int or_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] | vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int ori_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] | signed_imm;
    vm->pc += 4;
    return 0;
}

int and_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] & vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int andi_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] & signed_imm;
    vm->pc += 4;
    return 0;
}

int sll_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] << vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int srl_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = vm->regs[rs1] >> vm->regs[rs2];
    vm->pc += 4;
    return 0;
}

int sra_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = (vm->regs[rs1] >> vm->regs[rs2]) | (vm->regs[rs1] << (32 - vm->regs[rs2]));
    vm->pc += 4;
    return 0;
}

// Memory access
int lb_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    uint32_t mem_address = vm->regs[rs1] + signed_imm;
        if (rd == 0) {
        vm->pc += 4;
        return 0;
    }

    uint32_t mem_address = vm->regs[rs1] + signed_imm;

    if (DATA_MEM_START <= mem_address && mem_address <= DATA_MEM_END) {
        uint32_t mem_value = vm->data_mem[mem_address];
        vm->regs[rd] = ((int32_t)(mem_value & 0xFF) << 24) >> 24;
    }
    else if (INST_MEM_START <= mem_address && mem_address <= INST_MEM_END) {
        uint32_t mem_value = vm->instruction_mem[mem_address];
        vm->regs[rd] = ((int32_t)(mem_value & 0xFF) << 24) >> 24;
    }
    else if (VIRTUAL_ROUTINES_START <= mem_address && mem_address <= VIRTUAL_ROUTINES_END) {

    }
    else if (HEAP_BANKS_START <= mem_address && mem_address <= HEAP_BANKS_END) {

    }
    else {
        register_dump(instruction, vm);
    }

    vm->pc += 4;
    return 0;
}

int lh_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int lw_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
int lbu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int lhu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int sb_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int sh_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int sw_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);

// Program flow
int slt_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int slti_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int sltu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm);
int sltiu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm);
int beq_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int bne_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int blt_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int bltu_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, uint32_t unsigned_imm, VM *vm);
int bge_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm);
int bgeu_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, uint32_t unsigned_imm, VM *vm);
int jal_inst(uint32_t instruction, uint8_t rd, int32_t signed_imm, VM *vm);
int jalr_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm);
