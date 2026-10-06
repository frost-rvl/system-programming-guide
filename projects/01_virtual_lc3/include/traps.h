#ifndef TRAPS_H
#define TRAPS_H

enum {
  TRAP_GETC =
      0x20, /* get character from keyboard, not echoed onto the terminaml */
  TRAP_OUT = 0x21,   /* output a charachter */
  TRAP_PUTS = 0x22,  /* output a word string */
  TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
  TRAP_PUTSP = 0x24, /* output a byte string */
  TRAP_HALT = 0x25   /* halt the program */
};

void trap_getc();
void trap_out();
void trap_puts();
void trap_in();
void trap_putsp();
void trap_halt(int *running);

#endif // TRAPS_H
