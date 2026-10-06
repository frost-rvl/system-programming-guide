#include "vga.h"
#include "../../io/io.h"
#include "../../lib/math.h"

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/* Frame Buffer */
#define FB_ROW_COUNT 25
#define FB_COLUMN_COUNT 80
#define FB_TAB_SIZE 4
#define FB_CELL_SIZE 2
#define FB_FG_COLOR FB_GREEN
#define FB_BG_COLOR FB_BLACK

PRIVATE volatile char *fb = (char *)0x000B8000;
// the frame buffer pointer
PRIVATE unsigned short cursor_pos = 0;
// the cursor position

/* fb_write_cell
 * Writes a character with the given foreground and background to position i
 *
 * i : position in the framebuffer (1d)
 * c : character
 * fg : foreground color
 * bg : background color
 * */
PRIVATE void fb_write_cell(unsigned int i, char c, unsigned char fg,
                           unsigned char bg) {
  fb[i * FB_CELL_SIZE] = c;
  fb[i * FB_CELL_SIZE + 1] = ((bg & 0x0F) << 4 | (fg & 0x0F));
  // i * FB_CELL_SIZE because VGA hold a character information on
  // TODO : Signal this changement to the book repo
}

/* fb_move_cell
 * Move a cell index information into another cell index
 *
 * i : destination cell
 * j : origin cell
 * */
PRIVATE void fb_move_cell(unsigned int i, unsigned int j) {
  fb[i * FB_CELL_SIZE] = fb[j * FB_CELL_SIZE];
  fb[i * FB_CELL_SIZE + 1] = fb[j * FB_CELL_SIZE + 1];
}

/* fb_clear_row
 * Clear x row with ' ' character
 *
 * x : the row index
 * */
PRIVATE void fb_clear_row(unsigned int x) {
  for (unsigned int i = 0; i < FB_COLUMN_COUNT; i++) {
    fb_write_cell(index_2d(i, x, FB_COLUMN_COUNT), ' ', FB_FG_COLOR,
                  FB_BG_COLOR);
  }
}

/* fb_scroll
 * Scroll the framebuffer by decaling line by line
 *
 * */
PRIVATE void fb_scroll() {
  for (unsigned int j = 0; j < FB_ROW_COUNT - 1; j++) {
    for (unsigned int k = 0; k < FB_COLUMN_COUNT; k++) {
      fb_move_cell(index_2d(k, j, FB_COLUMN_COUNT),
                   index_2d(k, j + 1, FB_COLUMN_COUNT));
    }
  }
  fb_clear_row(FB_ROW_COUNT - 1);
  cursor_pos = FB_COLUMN_COUNT * (FB_ROW_COUNT - 1);
}

/* fb_move_cursor
 * Moves the cursor of the framebuffer to the given position
 *
 * pos : the new position of the cursor
 * */

PRIVATE void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

PUBLIC int fb_write(char *buf, unsigned int len) {
  unsigned i = 0;
  for (i = 0; i < len; i++) {
    if (buf[i] == '\n') {
      cursor_pos = next_multiple(cursor_pos, FB_COLUMN_COUNT);
    } else if (buf[i] == '\t') {
      cursor_pos = next_multiple(cursor_pos, FB_TAB_SIZE);
    } else if (buf[i] == '\b') {
      cursor_pos = cursor_pos == 0 ? 0 : cursor_pos - 1;
    } else {
      fb_write_cell(cursor_pos, buf[i], FB_FG_COLOR, FB_BG_COLOR);
      cursor_pos++;
    }

    if (cursor_pos >= FB_ROW_COUNT * FB_COLUMN_COUNT) {
      fb_scroll();
    }
  }
  fb_move_cursor(cursor_pos);
  return (int)i; // TODO: Need to be checked twice
}
