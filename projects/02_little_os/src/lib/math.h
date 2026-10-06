#ifndef MATH_H
#define MATH_H

/* index_2d
 * Transform a 2d coordonate into 1d index
 *
 * x : the row position
 * y : the columnn position
 * width : the size of on row
 * return -
 * */
unsigned int index_2d(unsigned x, unsigned y, unsigned int width);

/* next_multiple
 * Find the next multiple of a number superior to a reference value
 *
 * value : the reference value
 * multiple : the multiple base
 * */
unsigned int next_multiple(unsigned int value, unsigned int multiple);

#endif // MATH_H
