#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

enum {
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};

void update_flags(uint16_t r);

#endif /* FLAGS_H */
