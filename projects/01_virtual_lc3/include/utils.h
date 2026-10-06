#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

uint16_t sign_extend(uint16_t x, int bit_count);
int read_image(const char *image_path);
void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);
uint16_t check_key();

#endif // UTILS_H
