#include "../include/flags.h"
#include "../include/memory.h"
#include "../include/opcodes.h"
#include "../include/registers.h"
#include "../include/traps.h"
#include "../include/utils.h"

#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define PC_START 0x3000

extern uint16_t reg[R_COUNT];
extern uint16_t memory[MEMORY_MAX];

int main(int argc, const char *argv[]) {

  /*Loading arguments*/
  if (argc < 2) {
    printf("lc3 [image-file1] ...\n");
    exit(2);
  }

  for (int j = 1; j < argc; j++) {
    if (!read_image(argv[j])) {
      printf("failed to load image: %s\n", argv[j]);
      exit(1);
    }
  }

  /*Setup*/
  signal(SIGINT, handle_interrupt);
  disable_input_buffering();

  /*reset the condition flag*/
  reg[R_COND] = FL_ZRO;

  /*set the PC to start position*/
  /*0x3000 is the default*/
  reg[R_PC] = PC_START;

  int running = 1;
  while (running) {

    /*FETCH*/
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12;

    switch (op) {
    case OP_ADD: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* first operand (SR1) */
      uint16_t sr1 = (instr >> 6) & 0x7;
      /* whether we are in immediate mode */
      uint16_t imm_flag = (instr >> 5) & 0x1;

      if (imm_flag) {
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[dr] = reg[sr1] + imm5;

      } else {
        uint16_t sr2 = instr & 0x7;
        reg[dr] = reg[sr1] + reg[sr2];
      }

      update_flags(dr);

    } break;
    case OP_AND: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* first operand (SR1) */
      uint16_t sr1 = (instr >> 6) & 0x7;
      /* whether we are in immediate mode */
      uint16_t imm_flag = (instr >> 5) & 0x1;

      if (imm_flag) {
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[dr] = reg[sr1] & imm5;
      } else {
        uint16_t sr2 = instr & 0x7;
        reg[dr] = reg[sr1] & reg[sr2];
      }

      update_flags(dr);
    } break;
    case OP_NOT: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* source operand (SR) */
      uint16_t sr = (instr >> 6) & 0x7;

      reg[dr] = ~reg[sr];

      update_flags(dr);
    } break;
    case OP_BR: {
      /* flags */
      uint16_t cond_flag = (instr >> 9) & 0x7;
      /* PCoffset */
      uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

      if (cond_flag & reg[R_COND]) {
        reg[R_PC] += pc_offset;
      }

    } break;
    case OP_JMP: {
      /* baseR register */
      /* RET is a specific case of JMP where baseR = 111 (R7) */
      uint16_t br = (instr >> 6) & 0x7;
      reg[R_PC] = reg[br];

    } break;
    case OP_JSR: {
      /* jump register condition */
      uint16_t long_flag = (instr >> 11) & 0x1;
      /* saving PC to R7 */
      reg[R_R7] = reg[R_PC];

      if (long_flag) {
        uint16_t long_pc_offset = sign_extend(instr & 0x7FF, 11);
        reg[R_PC] += long_pc_offset; /* JSR */
      } else {
        uint16_t br = (instr >> 6) & 0x7;
        reg[R_PC] = reg[br]; /* JSRR */
      }
    } break;
    case OP_LD: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* PCoffset */
      uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

      reg[dr] = mem_read(reg[R_PC] + pc_offset);
      update_flags(dr);
    } break;
    case OP_LDI: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* PCoffset 9*/
      uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

      /* add pc_offset to the current PC, look at that memory location to get
       * the final address */
      reg[dr] = mem_read(mem_read(reg[R_PC] + pc_offset));

      update_flags(dr);
    } break;
    case OP_LDR: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* baseR register */
      uint16_t br = (instr >> 6) & 0x7;
      /* offset6 */
      uint16_t offset6 = sign_extend(instr & 0x3F, 6);

      reg[dr] = mem_read(reg[br] + offset6);
      update_flags(dr);
    } break;
    case OP_LEA: {
      /* destination register (DR) */
      uint16_t dr = (instr >> 9) & 0x7;
      /* PCoffset */
      uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

      reg[dr] = reg[R_PC] + pc_offset;
      update_flags(dr);
    } break;
    case OP_ST: {
      /* source register */
      uint16_t sr = (instr >> 9) & 0x7;
      /* PCoffset */
      uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

      mem_write(reg[R_PC] + pc_offset, reg[sr]);
    } break;
    case OP_STI: {
      /* source register */
      uint16_t sr = (instr >> 9) & 0x7;
      /* PCoffset */
      uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

      mem_write(mem_read(reg[R_PC] + pc_offset), reg[sr]);
    } break;
    case OP_STR: {
      /* source register */
      uint16_t sr = (instr >> 9) & 0x7;
      /* baseR */
      uint16_t br = (instr >> 6) & 0x7;
      /* offset6 */
      uint16_t offset6 = sign_extend(instr & 0x3F, 6);

      mem_write(reg[br] + offset6, reg[sr]);
    } break;
    case OP_TRAP: {
      /* SHOULD BE IMPLEMENTED WITH ASSEMBLY */
      /* BUT NOT WHEN WE USE VMS */
      reg[R_R7] = reg[R_PC];

      switch (instr & 0xFF) {
      case TRAP_GETC:
        trap_getc();
        break;
      case TRAP_OUT:
        trap_out();
        break;
      case TRAP_PUTS:
        trap_puts();
        break;
      case TRAP_IN:
        trap_in();
        break;
      case TRAP_PUTSP:
        trap_putsp();
        break;
      case TRAP_HALT:
        trap_halt(&running);
        break;
      }
    } break;
    case OP_RES:
    case OP_RTI:
    default:
      abort();
      break;
    }
  }

  /*Shutdown*/
  restore_input_buffering();
}
