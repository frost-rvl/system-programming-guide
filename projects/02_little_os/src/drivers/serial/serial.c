#include "serial.h"
#include "../../io/io.h"

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports int the same
 * order, but they start at different values
 * */

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 * */

#define SERIAL_LINE_ENABLE_DLAB 0x80

/* serial_is_transmit_fifo_empty
 * Checks whether the transmit FIFO queue  is empty or not for the given COM
 * port.
 *
 * com : The COM port
 * return - 0 if the transmit FIFO queue is not empty ( the port is not ready )
 *          1 if the transmit FIFO queue is empty ( the port is ready )
 * */

PRIVATE int serial_is_transmit_fifo_empty(unsigned int com) {
  /* 0x20 = 0010 0000 a filter to the corresponding bit on the status */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

PUBLIC void serial_configure_baud_rate(unsigned short com,
                                       unsigned short divisor) {
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

PUBLIC void serial_configure_line(unsigned short com) {
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
  // Enable Data bits
}

PUBLIC void serial_configure_buffers(unsigned short com) {
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

PUBLIC void serial_configure_modem(unsigned short com) {
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
  // Enable DTR and RTS
}

PUBLIC int serial_write(unsigned short com, char *buf, unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++) {
    while (serial_is_transmit_fifo_empty(com) == 0)
      ;
    outb(SERIAL_DATA_PORT(com), buf[i]);
  }
  return i;
}
