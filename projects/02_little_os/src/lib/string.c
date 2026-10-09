#include "./string.h"

PRIVATE void reverse(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    end--;
    start++;
  }
}

PUBLIC int strlen(char *str) {
  unsigned int i;
  for (i = 0; str[i] != '\0'; i++)
    ;
  return i;
}

PUBLIC char *itoa(int num, char *str, int base) {
  int i = 0;
  char isNegative = 0;
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // In standard itoa(), negative numbers are handled only with base 10
  if (num < 0 && base == 10) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (isNegative)
    str[i++] = '-';

  reverse(str, i);

  return str;
}

PUBLIC char *utoa(unsigned int num, char *str, int base) {
  int i = 0;
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  reverse(str, i);

  return str;
}
