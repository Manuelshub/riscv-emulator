#include "../include/execution.h"
#include <stdbool.h>

bool execute_instruction(cpu_state *cpu, decoded_instruction decoded) {
	uint32_t x1, x2, result;

	if (cpu == NULL)
		return false;
	
	switch (decoded.op) {
		case OP_ADD:
			if (!cpu_read_register(cpu, decoded.rs1, &x1))
				return false;
			if (!cpu_read_register(cpu, decoded.rs2, &x2))
				return false;
			result = x1 + x2;
			if (!cpu_write_register(cpu, decoded.rd, result))
				return false;
			return true;
		case OP_SUB:
			if (!cpu_read_register(cpu, decoded.rs1, &x1))
				return false;
			if (!cpu_read_register(cpu, decoded.rs2, &x2))
				return false;
			result = x1 - x2;
			if (!cpu_write_register(cpu, decoded.rd, result))
				return false;
			return true;
		case OP_ADDI:
			if (!cpu_read_register(cpu, decoded.rs1, &x1))
				return false;
			result = x1 + (uint32_t)decoded.imm;
			if (!cpu_write_register(cpu, decoded.rd, result))
				return false;
			return true;
		default:
			return false;
	}
	return true;
}