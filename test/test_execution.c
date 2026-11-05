#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/cpu.h"
#include "../include/decoder.h"
#include "../include/execution.h"

static void assert_register_value(const cpu_state *cpu, uint8_t reg, uint32_t expected) {
	uint32_t actual = 0;

	assert(cpu_read_register(cpu, reg, &actual));
	assert(actual == expected);
}

static void test_add_operand_selection() {
	cpu_state cpu;
	decoded_instruction instr;
	
	cpu_init(&cpu);

	assert(cpu_write_register(&cpu, 4, 10));
	assert(cpu_write_register(&cpu, 5, 20));

	instr = (decoded_instruction){
		.op = OP_ADD,
		.rd = 7,
		.rs1 = 4,
		.rs2 = 5
	};
	assert(execute_instruction(&cpu, instr));
	assert_register_value(&cpu, instr.rd, 30);
}

static void test_sub() {
	cpu_state cpu;
	decoded_instruction instr;
	
	cpu_init(&cpu);
	assert(cpu_write_register(&cpu, 2, 20));
	assert(cpu_write_register(&cpu, 3, 5));

	instr.op = OP_SUB;
	instr.rd = 6;
	instr.rs1 = 2;
	instr.rs2 = 3;

	assert(execute_instruction(&cpu, instr));
	assert_register_value(&cpu, 6, 15);
}

static void test_addi_positive() {
	cpu_state cpu;
	decoded_instruction instr;

	cpu_init(&cpu);
	assert(cpu_write_register(&cpu, 1, 20));

	instr = (decoded_instruction){
		.op = OP_ADDI,
		.rd = 3,
		.rs1 = 1,
		.imm = 10
	};

	assert(execute_instruction(&cpu, instr));
	assert_register_value(&cpu, 3, 30);
}

static void test_addi_negative() {
	cpu_state cpu;
	decoded_instruction instr;

	cpu_init(&cpu);
	assert(cpu_write_register(&cpu, 1, 20));

	instr = (decoded_instruction){
		.op = OP_ADDI,
		.rd = 3,
		.rs1 = 1,
		.imm = -5
	};
	assert(execute_instruction(&cpu,  instr));
	assert_register_value(&cpu, instr.rd, 15);
}

static void test_x0_invariant() {
	cpu_state cpu;
	decoded_instruction instr;

	assert(cpu_write_register(&cpu, 1, 5));
	assert(cpu_write_register(&cpu, 2, 7));
	instr = (decoded_instruction){
		.op = OP_ADD,
		.rd = 0,
		.rs1 = 1,
		.rs2 = 2
	};
	assert(execute_instruction(&cpu, instr));
	assert_register_value(&cpu, instr.rd, 0);
}

static void test_add_overflow(void) {
    cpu_state cpu;
    cpu_init(&cpu);

    assert(cpu_write_register(&cpu, 4, UINT32_MAX));
    assert(cpu_write_register(&cpu, 5, 1));

    decoded_instruction instruction = {
        .op = OP_ADD,
        .rd = 7,
        .rs1 = 4,
        .rs2 = 5
    };

    assert(execute_instruction(&cpu, instruction));
    assert_register_value(&cpu, 7, 0);
}

static void test_unsupported_instruction(void) {
    cpu_state cpu;
    cpu_init(&cpu);

    decoded_instruction instruction = {
        .op = (Operation)999
    };

    assert(!execute_instruction(&cpu, instruction));
}

/* 8. Verify NULL CPU is rejected. */
static void test_null_cpu(void) {
    decoded_instruction instruction = {
        .op = OP_ADD,
        .rd = 3,
        .rs1 = 1,
        .rs2 = 2
    };

    assert(!execute_instruction(NULL, instruction));
}

/* 9. Verify invalid source register is rejected. */
static void test_invalid_source_register(void) {
    cpu_state cpu;
    cpu_init(&cpu);

    decoded_instruction instruction = {
        .op = OP_ADD,
        .rd = 3,
        .rs1 = 32,
        .rs2 = 2
    };

    assert(!execute_instruction(&cpu, instruction));
}

/* 10. Verify invalid destination register is rejected. */
static void test_invalid_destination_register(void) {
    cpu_state cpu;
    cpu_init(&cpu);

    assert(cpu_write_register(&cpu, 1, 10));
    assert(cpu_write_register(&cpu, 2, 20));

    decoded_instruction instruction = {
        .op = OP_ADD,
        .rd = 32,
        .rs1 = 1,
        .rs2 = 2
    };

    assert(!execute_instruction(&cpu, instruction));
}

int main(void) {
	test_add_operand_selection();
	test_sub();
	test_addi_positive();
	test_addi_negative();
	test_x0_invariant();
	test_add_overflow();
	test_unsupported_instruction();
	test_null_cpu();
	test_invalid_source_register();
	test_invalid_destination_register();

	printf("All execution tests passed\n");
}