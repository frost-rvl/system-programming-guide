#ifndef VGA_H
#define VGA_H

/* Available colors handeld by the framebuffer of VGA
 * */
enum {
  FB_BLACK = 0,
  FB_BLUE,
  FB_GREEN,
  FB_CYAN,
  FB_RED,
  FB_MAGENTA,
  FB_BROWN,
  FB_LIGHT_GREY,
  FB_DARK_GREY,
  FB_LIGHT_BLUE,
  FB_LIGHT_GREEN,
  FB_LIGHT_CYAN,
  FB_LIGHT_RED,
  FB_LIGHT_MAGENTA,
  FB_LIGHT_BROWN,
  FB_WHITE
};

/* fb_write
 * Writes contents of the buffer of length len to the screen
 *
 * buf : data to send through VGA
 * len : the length of the buffer
 * return - number of character printed
 * */

int fb_write(char *buf, unsigned int len);

#endif // VGA_H
