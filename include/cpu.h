#ifndef CPU_H
#define CPU_H

#include "decoder.h"

#define MAX_REGISTER_LEN 32

typedef struct {
	uint32_t registers[MAX_REGISTER_LEN];
	uint32_t pc;
} cpu_state;

void cpu_init(cpu_state *cpu);
bool cpu_read_register(const cpu_state *cpu, uint8_t reg, uint32_t *value);
bool cpu_write_register(cpu_state *cpu, uint8_t reg, uint32_t value);
uint32_t cpu_get_pc(const cpu_state *cpu);
void cpu_set_pc(cpu_state *cpu, uint32_t address);

#endif