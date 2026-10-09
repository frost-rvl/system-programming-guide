#ifndef STRING_H
#define STRING_H

/* strlen
 * Return the number of characters of a string
 *
 * str : the input string
 * */
int strlen(char *str);

/* itoa
 * Convert an integer to string
 *
 * num : the integer
 * str : the buffer to store the string
 * bas : the base number of the integer
 * */
char *itoa(int num, char *str, int base);

/* utoa
 * Convert an unsigned integer to string
 *
 * num : the unsigned integer
 * str : the buffer to store the string
 * bas : the base number of the integer
 * */
char *utoa(unsigned int num, char *str, int base);

#endif // !STRING_H
