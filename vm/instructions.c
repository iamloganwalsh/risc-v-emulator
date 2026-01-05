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
    vm->regs[rd] = (int32_t)vm->regs[rs1] >> (vm->regs[rs2] & 0x1F);
    vm->pc += 4;
    return 0;
}

// Memory access
int lb_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {

    uint32_t mem_address = vm->regs[rs1] + signed_imm;
    uint8_t byteval;
    int32_t loadedval;

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        uint32_t val = 0;
        int vr_result = check_vr(instruction, mem_address, &val, vm);
    if (vr_result == 0) {
        if (rd != 0) {
            uint8_t byteval = val & 0xFF;
            int32_t loadedval = ((int32_t)(byteval) << 24) >> 24;  // Sign extend
            vm->regs[rd] = loadedval;
        }
        vm->pc += 4;
        return 0;
    }
        // If its a virtual routine but didn't map to a valid VR address, throw an error
        register_dump(instruction, vm);
        exit(1);
    }

    else if (DATA_MEM_START <= mem_address && mem_address <= DATA_MEM_END) {
        byteval = vm->data_mem[mem_address - DATA_MEM_START]; 
    }
    else if (INST_MEM_START <= mem_address && mem_address <= INST_MEM_END) {
        byteval = vm->instruction_mem[mem_address];    // Retrieve 8byte value
    }
    else if (HEAP_BANK_START <= mem_address && mem_address <= HEAP_BANK_END) {
        byteval = vm->heapbank.memory[mem_address - HEAP_BANK_START];
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    // Sext and store the result
    if (rd != 0) {
        loadedval = ((int32_t)(byteval) << 24) >> 24;
        vm->regs[rd] = loadedval;
    }

    vm->pc += 4;
    return 0;
}

int lh_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {

    uint32_t mem_address = vm->regs[rs1] + signed_imm;
    uint16_t twobyteval;
    int32_t loadedval;

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        uint32_t val = 0;
        int vr_result = check_vr(instruction, mem_address, &val, vm);

        if (vr_result == 0) {
            if (rd != 0) {
                uint8_t byteval = val & 0xFFFF;
                int32_t loadedval = ((int32_t)(byteval) << 16) >> 16;  // Sign extend
                vm->regs[rd] = loadedval;
            }
            vm->pc += 4;
            return 0;
        }

        // If its a virtual routine but didn't map to a valid VR address, throw an error
        register_dump(instruction, vm);
        exit(1);
    }

    else if (DATA_MEM_START <= mem_address && mem_address + 1 <= DATA_MEM_END) {
        twobyteval = (vm->data_mem[mem_address - DATA_MEM_START]) | (vm->data_mem[mem_address - DATA_MEM_START + 1] << 8); 
    }
    else if (INST_MEM_START <= mem_address && mem_address + 1 <= INST_MEM_END) {
        twobyteval = (vm->instruction_mem[mem_address]) | (vm->instruction_mem[mem_address + 1] << 8);
    }
    else if (HEAP_BANK_START <= mem_address && mem_address + 1 <= HEAP_BANK_END) {
        twobyteval = (vm->heapbank.memory[mem_address - HEAP_BANK_START]) |
                     (vm->heapbank.memory[mem_address - HEAP_BANK_START + 1] << 8);
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    // Sext and store the result
    if (rd != 0) {
        loadedval = ((int32_t)(twobyteval) << 16) >> 16;
        vm->regs[rd] = loadedval;
    }

    vm->pc += 4;
    return 0;
}

int lw_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    
    uint32_t mem_address = vm->regs[rs1] + signed_imm;
    uint32_t word;

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        uint32_t val = 0;
        int vr_result = check_vr(instruction, mem_address, &val, vm);
        if (vr_result == 0) {

            if (rd != 0) {
                vm->regs[rd] = val;
            }
            vm->pc += 4;
            return 0;
        }
        // If its a virtual routine but didn't map to a valid VR address, throw an error
        register_dump(instruction, vm);
        exit(1);
    }

    else if (DATA_MEM_START <= mem_address && mem_address + 3 <= DATA_MEM_END) {
        word = (vm->data_mem[mem_address - DATA_MEM_START]) | (vm->data_mem[mem_address - DATA_MEM_START + 1] << 8) |
        (vm->data_mem[mem_address - DATA_MEM_START + 2] << 16) | (vm->data_mem[mem_address - DATA_MEM_START + 3] << 24); 
    }
    else if (INST_MEM_START <= mem_address && mem_address + 3 <= INST_MEM_END) {
        word = (vm->instruction_mem[mem_address]) | (vm->instruction_mem[mem_address + 1] << 8) |
        (vm->instruction_mem[mem_address + 2] << 16) | (vm->instruction_mem[mem_address + 3] << 24);
    }
    else if (HEAP_BANK_START <= mem_address && mem_address + 3 <= HEAP_BANK_END) {
        word = (vm->heapbank.memory[mem_address - HEAP_BANK_START]) |
                     (vm->heapbank.memory[mem_address - HEAP_BANK_START + 1] << 8) |
                     (vm->heapbank.memory[mem_address - HEAP_BANK_START + 2] << 16) |
                     (vm->heapbank.memory[mem_address - HEAP_BANK_START + 3] << 24);
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    if (rd != 0) {
        vm->regs[rd] = word;
    }

    vm->pc += 4;
    return 0;
}

int lbu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm) {
    uint32_t mem_address = vm->regs[rs1] + unsigned_imm;
    uint8_t byteval;
    uint32_t loadedval;

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        uint32_t val = 0;
        int vr_result = check_vr(instruction, mem_address, &val, vm);
        if (vr_result == 0) {

            if (rd != 0) {
                vm->regs[rd] = val & 0xFF;
            }
            vm->pc += 4;
            return 0;
        }
        // If its a virtual routine but didn't map to a valid VR address, throw an error
        register_dump(instruction, vm);
        exit(1);
    }

    else if (DATA_MEM_START <= mem_address && mem_address <= DATA_MEM_END) {
        byteval = vm->data_mem[mem_address - DATA_MEM_START]; 
    }
    else if (INST_MEM_START <= mem_address && mem_address <= INST_MEM_END) {
        byteval = vm->instruction_mem[mem_address];
    }
    else if (HEAP_BANK_START <= mem_address && mem_address <= HEAP_BANK_END) {
        byteval = vm->heapbank.memory[mem_address - HEAP_BANK_START];
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    // Sext and store the result
    if (rd != 0) {
        vm->regs[rd] = (uint32_t)(byteval);
    }

    vm->pc += 4;
    return 0;
}

int lhu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm) {
    uint32_t mem_address = vm->regs[rs1] + unsigned_imm;
    uint16_t twobyteval;
    uint32_t loadedval;

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        uint32_t val = 0;
        int vr_result = check_vr(instruction, mem_address, &val, vm);
        if (vr_result == 0) {

            if (rd != 0) {
                vm->regs[rd] = val & 0xFFFF;
            }
            vm->pc += 4;
            return 0;
        }
        // If its a virtual routine but didn't map to a valid VR address, throw an error
        register_dump(instruction, vm);
        exit(1);
    }

    else if (DATA_MEM_START <= mem_address && mem_address + 1 <= DATA_MEM_END) {
        twobyteval = (vm->data_mem[mem_address - DATA_MEM_START]) | (vm->data_mem[mem_address - DATA_MEM_START + 1] << 8); 
    }
    else if (INST_MEM_START <= mem_address && mem_address + 1 <= INST_MEM_END) {
        twobyteval = (vm->instruction_mem[mem_address]) | (vm->instruction_mem[mem_address + 1] << 8);
    }
    else if (HEAP_BANK_START <= mem_address && mem_address + 1 <= HEAP_BANK_END) {
        twobyteval = (vm->heapbank.memory[mem_address - HEAP_BANK_START]) |
                     (vm->heapbank.memory[mem_address - HEAP_BANK_START + 1] << 8);
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    // Sext and store the result
    if (rd != 0) {
        vm->regs[rd] = (uint32_t)(twobyteval);
    }

    vm->pc += 4;
    return 0;
}

int sb_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    uint32_t mem_address = vm->regs[rs1] + signed_imm;
    uint8_t byteval = vm->regs[rs2] & 0xFF;  // Get lowest byte

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        uint32_t val = byteval;
        int vr_result = check_vr(instruction, mem_address, &val, vm);
        if (vr_result >= 0) {
            vm->pc += 4;
            return 0;
        }
        register_dump(instruction, vm);
        exit(1);
    }
    else if (DATA_MEM_START <= mem_address && mem_address <= DATA_MEM_END) {
        vm->data_mem[mem_address - DATA_MEM_START] = byteval;
    }
    else if (INST_MEM_START <= mem_address && mem_address <= INST_MEM_END) {
        vm->instruction_mem[mem_address] = byteval;
    }
    else if (HEAP_BANK_START <= mem_address && mem_address <= HEAP_BANK_END) {
        vm->heapbank.memory[mem_address - HEAP_BANK_START] = byteval;
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    vm->pc += 4;
    return 0;
}

int sh_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    uint32_t mem_address = vm->regs[rs1] + signed_imm;
    uint32_t value = vm->regs[rs2];

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        int vr_result = check_vr(instruction, mem_address, &value, vm);
        if (vr_result >= 0) {
            vm->pc += 4;
            return 0;
        }
        register_dump(instruction, vm);
        exit(1);
    }
    else if (DATA_MEM_START <= mem_address && mem_address + 1 <= DATA_MEM_END) {
        uint32_t offset = mem_address - DATA_MEM_START;
        vm->data_mem[offset] = value & 0xFF;
        vm->data_mem[offset + 1] = (value >> 8) & 0xFF;
    }
    else if (INST_MEM_START <= mem_address && mem_address + 1 <= INST_MEM_END) {
        vm->instruction_mem[mem_address] = value & 0xFF;
        vm->instruction_mem[mem_address + 1] = (value >> 8) & 0xFF;
    }
    else if (HEAP_BANK_START <= mem_address && mem_address + 1 <= HEAP_BANK_END) {
        uint32_t offset = mem_address - HEAP_BANK_START;
        vm->heapbank.memory[offset] = value & 0xFF;
        vm->heapbank.memory[offset + 1] = (value >> 8) & 0xFF;
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    vm->pc += 4;
    return 0;
}

int sw_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    uint32_t mem_address = vm->regs[rs1] + signed_imm;
    uint32_t value = vm->regs[rs2];

    if (VIRTUAL_ROUTINE_START <= mem_address && mem_address <= VIRTUAL_ROUTINE_END) {
        int vr_result = check_vr(instruction, mem_address, &value, vm);
        if (vr_result >= 0) {
            vm->pc += 4;
            return 0;
        }
        register_dump(instruction, vm);
        exit(1);
    }
    else if (DATA_MEM_START <= mem_address && mem_address + 3 <= DATA_MEM_END) {
        uint32_t offset = mem_address - DATA_MEM_START;
        vm->data_mem[offset] = value & 0xFF;
        vm->data_mem[offset + 1] = (value >> 8) & 0xFF;
        vm->data_mem[offset + 2] = (value >> 16) & 0xFF;
        vm->data_mem[offset + 3] = (value >> 24) & 0xFF;
    }
    else if (INST_MEM_START <= mem_address && mem_address + 3 <= INST_MEM_END) {
        vm->instruction_mem[mem_address] = value & 0xFF;
        vm->instruction_mem[mem_address + 1] = (value >> 8) & 0xFF;
        vm->instruction_mem[mem_address + 2] = (value >> 16) & 0xFF;
        vm->instruction_mem[mem_address + 3] = (value >> 24) & 0xFF;
    }
    else if (HEAP_BANK_START <= mem_address && mem_address + 3 <= HEAP_BANK_END) {
        uint32_t offset = mem_address - HEAP_BANK_START;
        vm->heapbank.memory[offset] = value & 0xFF;
        vm->heapbank.memory[offset + 1] = (value >> 8) & 0xFF;
        vm->heapbank.memory[offset + 2] = (value >> 16) & 0xFF;
        vm->heapbank.memory[offset + 3] = (value >> 24) & 0xFF;
    }
    else {
        register_dump(instruction, vm);
        exit(1);
    }

    vm->pc += 4;
    return 0;
}

// Program Flow
int slt_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = ((int32_t)vm->regs[rs1] < (int32_t)vm->regs[rs2]) ? 1 : 0;
    vm->pc += 4;
    return 0;
}

int slti_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = ((int32_t)vm->regs[rs1] < signed_imm) ? 1 : 0;
    vm->pc += 4;
    return 0;
}

int sltu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint8_t rs2, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = (vm->regs[rs1] < vm->regs[rs2]) ? 1 : 0;
    vm->pc += 4;
    return 0;
}

int sltiu_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, uint32_t unsigned_imm, VM *vm) {
    if (rd == 0) {
        vm->pc += 4;
        return 0;
    }
    vm->regs[rd] = (vm->regs[rs1] < unsigned_imm) ? 1 : 0;
    vm->pc += 4;
    return 0;
}

int beq_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    if (vm->regs[rs1] == vm->regs[rs2]) {
        vm->pc += signed_imm;
    } else {
        vm->pc += 4;
    }
    return 0;
}

int bne_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    if (vm->regs[rs1] != vm->regs[rs2]) {
        vm->pc += signed_imm;
    } else {
        vm->pc += 4;
    }
    return 0;
}

int blt_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    if ((int32_t)vm->regs[rs1] < (int32_t)vm->regs[rs2]) {
        vm->pc += signed_imm ;
    } else {
        vm->pc += 4;
    }
    return 0;
}

int bltu_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    if (vm->regs[rs1] < vm->regs[rs2]) {
        vm->pc += signed_imm;
    } else {
        vm->pc += 4;
    }
    return 0;
}

int bge_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    if ((int32_t)vm->regs[rs1] >= (int32_t)vm->regs[rs2]) {
        vm->pc += signed_imm;
    } else {
        vm->pc += 4;
    }
    return 0;
}

int bgeu_inst(uint32_t instruction, uint8_t rs1, uint8_t rs2, int32_t signed_imm, VM *vm) {
    if (vm->regs[rs1] >= vm->regs[rs2]) {
        vm->pc += signed_imm;
    } else {
        vm->pc += 4;
    }
    return 0;
}

int jal_inst(uint32_t instruction, uint8_t rd, int32_t signed_imm, VM *vm) {
    if (rd != 0) {
        vm->regs[rd] = vm->pc + 4;
    }
    vm->pc += signed_imm;   // Already shifted in decoding.c
    return 0;
}

int jalr_inst(uint32_t instruction, uint8_t rd, uint8_t rs1, int32_t signed_imm, VM *vm) {
    uint32_t target = (vm->regs[rs1] + signed_imm) & ~1; 
    if (rd != 0) {
        vm->regs[rd] = vm->pc + 4; 
    }
    vm->pc = target;
    return 0;
}
