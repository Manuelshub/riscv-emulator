#ifndef EXECUTION_H
#define EXECUTION_H

#include "cpu.h"

bool execute_instruction(cpu_state *cpu, decoded_instruction decoded);

#endif