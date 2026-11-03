#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
	OP_INVALID = 0,
	OP_ADD,
	OP_SUB,
	OP_ADDI,
	// OP_AND,
	// OP_OR,
	// OP_XOR,
	// OP_LOAD,
	// OP_STORE,
	// OP_BRANCH,
	// OP_JUMP
} Operation;

typedef struct {
	Operation op;
	uint8_t rd;
	uint8_t rs1;
	uint8_t rs2;
	int32_t imm;
} decoded_instruction;

bool decode_instruction(uint32_t instruction, decoded_instruction *decoded);

#endif