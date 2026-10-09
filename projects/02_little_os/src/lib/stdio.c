#include "./stdio.h"
#include "../drivers/serial/serial.h"
#include "../drivers/vga/vga.h"
#include "./string.h"

PRIVATE int dev_write(unsigned char device, char *buf, unsigned int len) {
  switch (device) {
  case DEVICE_SERIAL:
    return serial_write(SERIAL_COM1_BASE, buf, len);
  case DEVICE_VGA:
    return fb_write(buf, len);
  default:
    return EOF;
  }
}

PUBLIC int putchar(unsigned char device, char c) {
  if (dev_write(device, &c, 1) == EOF)
    return EOF;
  return (unsigned char)c;
}

PUBLIC int vprintf(unsigned char device, const char *fmt, va_list list) {
  int total = 0;
  for (unsigned int i = 0; fmt[i] != '\0'; i++) {
    if (fmt[i] != '%') {
      putchar(device, fmt[i]);
      total++;
      continue;
    }

    switch (fmt[++i]) {
    case 'c':
      putchar(device, (char)va_arg(list, int));
      total++;
      break;
    case 's': {
      char *arg = va_arg(list, char *);
      dev_write(device, arg, strlen(arg));
      total += strlen(arg);
      break;
    }
    case 'd': {
      int arg = va_arg(list, int);
      char buffer[100];
      char *arg_str = itoa(arg, buffer, 10);
      dev_write(device, arg_str, strlen(arg_str));
      total += strlen(arg_str);
      break;
    }
    case 'u': {
      unsigned int arg = va_arg(list, unsigned);
      char buffer[100];
      char *arg_str = utoa(arg, buffer, 10);
      dev_write(device, arg_str, strlen(arg_str));
      total += strlen(arg_str);
      break;
    }
    case 'x': {
      int arg = va_arg(list, unsigned int);
      char buffer[100];
      char *arg_str = itoa(arg, buffer, 16);
      dev_write(device, arg_str, strlen(arg_str));
      total += strlen(arg_str);
      break;
    }
    case '%': {
      putchar(device, '%');
      total++;
      break;
    }
    default: {
      putchar(device, fmt[i]);
      total++;
      break;
    }
    }
  }
  return total ? total : EOF;
}

PUBLIC int printf(unsigned char device, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int n = vprintf(device, fmt, ap);
  va_end(ap);
  return n;
}
