#include "./math.h"

PUBLIC unsigned int index_2d(unsigned x, unsigned y, unsigned int width) {
  return x + y * width;
}

PUBLIC unsigned int next_multiple(unsigned int value, unsigned int multiple) {
  return ((value / multiple) + 1) * multiple;
}
