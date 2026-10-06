#include "../drivers/serial/serial.h"
#include "../drivers/vga/vga.h"

int kmain() {
  /* Configure COM1 */
  serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
  serial_configure_line(SERIAL_COM1_BASE);
  serial_configure_buffers(SERIAL_COM1_BASE);
  serial_configure_modem(SERIAL_COM1_BASE);

  /* VGA test */
  char *buf = "----------Hello World!----------\n";
  fb_write(buf, 33);

  // char *buf2 = "Little_os is actually working...";
  //  fb_write(buf2, 32);

  // char *buf3 = "\nhello worl\b\bd";
  //  fb_write(buf3, 14);

  /* Scroll test */
  // char line[9] = "\nLine 00";
  // int i;
  // for (i = 1; i < 30; i++) {
  // line[6] = '0' + (i / 10);
  // line[7] = '0' + (i % 10);
  // fb_write(line, 8);
  //}

  // char *end = "Hello\nGuys";
  // fb_write(end, 10);

  /* Serial Test */
  char *buf4 = "Hello Other World\n";
  serial_write(SERIAL_COM1_BASE, buf4, 18);

  return 35;
}
