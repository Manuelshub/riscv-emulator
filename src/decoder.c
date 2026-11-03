#include "../include/decoder.h"
#include <stdint.h>

/*
 * decode_instruction - decodes the instruction binary, breaking down it's part into
 * 						it's appropriate register, opcode, e.t.c
 */
int decode_instruction(uint32_t instruction, decoded_instruction *decoded) {
	uint32_t opcode, raw_imm;
	uint8_t rd, funct3, rs1, rs2, funct7;

	if (decoded == NULL)
		return 0;

	*decoded = (decoded_instruction){0};
	opcode = instruction & 0x7F;
	rd = (instruction >> 7) & 0x1F;
	funct3 = (instruction >> 12) & 0x07;
	rs1 = (instruction >> 15) & 0x1F;
	rs2 = (instruction >> 20) & 0x1F;
	funct7 = (instruction >> 25) & 0x7F;

	decoded->rd = rd;
	decoded->rs1 = rs1;
	
	if (opcode == 0x33) {
		if (funct3 == 0x0 && funct7 == 0x00)
			decoded->op = OP_ADD;
		else if (funct3 == 0x0 && funct7 == 0x20)
			decoded->op = OP_SUB;
		else
			return 0;

		decoded->rs2 = rs2;
	}
	else if (opcode == 0x13) {
		if (funct3 == 0x0)
			decoded->op = OP_ADDI;
		else
			return 0;
		raw_imm = instruction >> 20;
		decoded->imm = sign_extend(raw_imm, 12);
	}
	else
		return 0;

	return 1;
}

static int32_t sign_extend(uint32_t value, unsigned bits) {
	uint32_t sign_bit = 1u << (bits - 1);

	return (int32_t)((value ^ sign_bit) - sign_bit);
}