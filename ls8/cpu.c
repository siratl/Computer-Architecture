#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Read RAM inside CPU struct at given index
 */
unsigned char cpu_ram_read(struct cpu *cpu, unsigned int index)
{
  return cpu->ram[index];
}

/**
 * Write a value to the RAM inside CPU struct at given index
 */
void cpu_ram_write(struct cpu *cpu, unsigned int index, unsigned char value)
{
  cpu->ram[index] = value;
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);
    // 2. Figure out how many operands this next instruction requires
    int operands = IR >> 6;
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA, operandB;
    if (operands > 0)
    {
      operandA = cpu_ram_read(cpu, cpu->pc + 1);
      if (operands > 1)
      {
        operandB = cpu_ram_read(cpu, cpu->pc + 2);
      }
    }
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    switch (IR)
    {
    case LDI:
      cpu_ram_write(cpu, operandA, operandB);
      break;
    case PRN:
      printf("%d\n", cpu_ram_read(cpu, operandA));
      break;
    default:
      printf("Error - Instruction Register Unknown at register PC index {%d}\n", cpu->pc);
      running = 0;
      break;
    }
    // 6. Move the PC to the next instruction.
    cpu->pc += operands + 1;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers

  // * `R0`-`R6` are cleared to `0`.
  memset(cpu->reg, 0, 8 * sizeof(unsigned char));

  // * `R7` is set to `0xF4`.
  cpu->reg[7] = 0xF4;

  // * `PC` and `FL` registers are cleared to `0`.
  cpu->pc = 0;

  // * RAM is cleared to `0`.
  memset(cpu->ram, 0, 256 * sizeof(unsigned char));
}
