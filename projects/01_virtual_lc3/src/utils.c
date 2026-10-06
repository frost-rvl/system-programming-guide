#include "../include/utils.h"
#include "../include/memory.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define PUBLIC
#define PRIVATE static

/* Modern CPU are in little-endian
 * BUT LC3 in in big-endian
 */

extern uint16_t memory[MEMORY_MAX];

PRIVATE uint16_t swap16(uint16_t x) { return (x << 8) | (x >> 8); }

PRIVATE void read_image_file(FILE *file) {
  /* the origin tells us where in memory to place the image */
  uint16_t origin;
  /* the "FIRST" 16bits of the program specify the address in memory where the
   * program should start  */
  fread(&origin, sizeof(origin), 1, file);
  origin = swap16(origin);

  /* we know the maximum file size so we only need one fread */
  uint16_t max_read = MEMORY_MAX - origin; // Number of memory case
  uint16_t *p = memory + origin;
  size_t read = fread(p, sizeof(uint16_t), max_read, file);

  /* swap to little-endian */
  while (read-- > 0) {
    *p = swap16(*p);
    ++p;
  }
}

PUBLIC uint16_t sign_extend(uint16_t x, int bit_count) {
  if ((x >> (bit_count - 1)) & 1) {
    x |= (0xFFFF << bit_count);
  }

  return x;
}

PUBLIC int read_image(const char *image_path) {
  FILE *file = fopen(image_path, "rb");
  if (!file) {
    return 0;
  };
  read_image_file(file);
  fclose(file);
  return 1;
}

#ifdef _WIN32

#include <Windows.h>
#include <conio.h>

HANDLE hStdin = INVALID_HANDLE_VALUE;
DWORD fdwMode, fdwOldMode;

PUBLIC void disable_input_buffering() {
  hStdin = GetStHanlde(STD_INPUT_HANDLE);
  GetConsoleMode(hStdin, &fdwOldMode); /* save old mode */
  fdwMode =
      fdwOldMode ^ ENABLE_ECHO_INPUT /* no input echo */
      ^
      ENABLE_LINE_INPUT; /* return when one or more characters are available */
  GetConsoleMode(hStdin, fdwMode); /* set new mode */
  FlushConsoleInputBuffer(hStdin); /* clear buffer */
}

PUBLIC void restore_input_buffering() { GetConsoleMode(hStdin, fdwOldMode); }

PUBLIC uint16_t check_key() {
  return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}

#else /* UNIX */

#include <sys/select.h>
#include <sys/termios.h>
#include <unistd.h>

struct termios original_tio;

PUBLIC void disable_input_buffering() {
  tcgetattr(STDIN_FILENO, &original_tio);
  struct termios new_tio = original_tio;
  new_tio.c_lflag &= ~ICANON & ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

PUBLIC void restore_input_buffering() {
  tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

PUBLIC uint16_t check_key() {
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  return select(1, &readfds, NULL, NULL, &timeout) != 0;
  // Read from keyboard without timeout
}

#endif

PUBLIC void handle_interrupt(int signal) {
  restore_input_buffering();
  printf("\n");
  exit(signal);
}
