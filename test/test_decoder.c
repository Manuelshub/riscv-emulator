#include "../include/decoder.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	uint32_t instruction;
	decoded_instruction decoded;
	int success;

	instruction = 0x002081B3;
	success = decode_instruction(instruction, &decoded);
	assert(success);
	assert(decoded.op == OP_ADD);
	assert(decoded.rd == 3);
	assert(decoded.rs1 == 1);
	assert(decoded.rs2 == 2);
	printf("Decoder test passed for ADD\n");

	instruction = 0x00A08193;
	success = decode_instruction(instruction, &decoded);
	assert(success);
	assert(decoded.op == OP_ADDI);
	assert(decoded.imm == 10);
	assert(decoded.rd == 3);
	assert(decoded.rs1 == 1);
	printf("Decoder test1 pass for ADDI\n");

	instruction = 0xFFB08193;
	success = decode_instruction(instruction, &decoded);
	assert(success);
	assert(decoded.op == OP_ADDI);
	assert(decoded.imm == -5);
	printf("Decoder test1 for ADDI negative passed\n");

	instruction = 0x80008193;
	success = decode_instruction(instruction, &decoded);
	assert(success);
	assert(decoded.op == OP_ADDI);
	assert(decoded.imm == -2048);
	printf("Decoder test1 for ADDI zero\n");

	return EXIT_SUCCESS;
}