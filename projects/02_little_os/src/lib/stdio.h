#ifndef STDIO_H
#define STDIO_H

#include "./stdarg.h"

/* Device type used by putchar */
enum { DEVICE_SERIAL, DEVICE_VGA };

/* DIFFERENT COLOR LEVEL */
enum { COLOR_DEBUG, COLOR_INFO, COLOR_ERROR, COLOR_RESET };

/* The value returned by putchar and similar functions to indicate the
   end of the file.  */
#define EOF (-1)

/* printf
 * Write the formatted string into specific device
 *
 * device : enum to define which device to send
 * fmt : the formatted text
 * ... : indicate that the function take variable argument list
 * */
int printf(unsigned char device, const char *fmt, ...);

/* vprintf
 * Sends formatted output to device using an argument list passed to it
 *
 * device : enum to define which device to send
 * fmt : the formatted text
 * va_list : variable argument list
 * */
int vprintf(unsigned char device, const char *fmt, va_list list);

/* putchar
 * Write one character into device
 *
 * device : enum to define which device to send
 * c : the character to print
 * */
int putchar(unsigned char device, char c);

/* set_color
 * Change the color of the output device
 *
 * device : the target device
 * level : the color level
 * */
void set_color(unsigned int device, unsigned int level);

#endif // STDIO_H
