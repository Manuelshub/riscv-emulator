#include "../include/cpu.h"
#include <stdint.h>


/*
 * validate_register - Validates register to ensure it's within bounds
 */
static int validate_register(uint8_t reg) {
	return reg < 32;
}

/*
 * cpu_init - Initializes the current cpu state to 0.
 */
void cpu_init(cpu_state *cpu) {
	size_t i;
	
	if (cpu == NULL)
		return;

	for (i = 0; i < MAX_REGISTER_LEN; i++) {
		cpu->registers[i] = 0;
	}
	cpu->pc = 0;
}

/*
 * cpu_read_register - reads the value of the appropriate cpu registers into the pointer
 * 					   value
 */
bool cpu_read_register(const cpu_state *cpu, uint8_t reg, uint32_t *value) {
	if (cpu == NULL)
		return false;
	if (value == NULL)
		return false;
	if (!validate_register(reg))
		return false;
	if (reg == 0) {
		*value = 0;
		return true;
	}
	*value = cpu->registers[reg];
	return true;
}

bool cpu_write_register(cpu_state *cpu, uint8_t reg, uint32_t value) {
	if (cpu == NULL)
		return false;
	if (!validate_register(reg))
		return false;
	if (reg == 0) {
		cpu->registers[reg] = 0;
		return true;
	}
	cpu->registers[reg] = value;
	return true;
}

/*
 * cpu_get_pc - retrieve the current Program counter value
 */
uint32_t cpu_get_pc(const cpu_state *cpu) {
	if (cpu == NULL)
		return 0;
	return cpu->pc;
}

void cpu_set_pc(cpu_state *cpu, uint32_t address) {
	if (cpu == NULL)
		return;
	cpu->pc = address;
}