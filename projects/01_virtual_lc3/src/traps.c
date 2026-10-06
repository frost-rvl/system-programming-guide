#include "../include/traps.h"
#include "../include/flags.h"
#include "../include/memory.h"
#include "../include/registers.h"
#include <stdint.h>
#include <stdio.h>

extern uint16_t reg[R_COUNT];
extern uint16_t memory[MEMORY_MAX];

void trap_getc() {
  reg[R_R0] = (uint16_t)getchar();
  update_flags(R_R0);
}

void trap_out() {
  putc((char)(reg[R_R0] & 0xFF), stdout);
  //  We can ommit 0xFF because char is 8bit
  fflush(stdout);
}

void trap_puts() {
  /* one char per word */
  uint16_t *c = memory + reg[R_R0];
  while (*c) {
    putc((char)*c, stdout);
    ++c;
  }
  fflush(stdout); // TODO: : remove this to see what's happening
}

void trap_in() {
  printf("Enter a character: ");
  char c = getchar();
  putc(c, stdout);
  fflush(stdout);
  reg[R_R0] = (uint16_t)c;
  update_flags(reg[R_R0]);
}

void trap_putsp() {
  /* one char per byte (two bytes per word)
   * here we need to swap to
   * big endian format
   */

  uint16_t *c = memory + reg[R_R0];
  while (*c) {
    char char1 = (*c) & 0xFF; // Take R0[7:0]
    putc(char1, stdout);
    char char2 = (*c) >> 8; // No need to put 0XFF because 16bit - 8bit = 8bit
    if (char2)
      putc(char2, stdout);
    ++c;
  }
  fflush(stdout);
}

void trap_halt(int *running) {
  puts("HALT");
  fflush(stdout);
  *running = 0;
}
