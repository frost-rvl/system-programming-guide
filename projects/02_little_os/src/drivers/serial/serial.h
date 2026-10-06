#ifndef SERIAL_H
#define SERIAL_H

/* Serial port */

#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */

/* serial_configure_baud_rate
 * Sets the speed of the data being sent. The default speed of a serial port is
 * 115200 bits/s. The argument is a divisor of that number, hence the resulting
 * speed becomes (115200 / divisor) bits/s
 *
 * com : The COM port to configure
 * divisor : The divisor
 * */

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/* serial_configure_line
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled
 *
 * com : The COM port to configure
 * */

void serial_configure_line(unsigned short com);

/* serial_configure_buffers
 * Configures the buffer of the given serial port. The port is set to have a
 * FIFO enabled, to clear both receiver and transmission FIFI queues and
 * use 14 bytes as size of queue
 *
 * com : The COM port to configure
 * */

void serial_configure_buffers(unsigned short com);

/* serial_configure_modem
 * Control the flow via RTS (Ready To Transmit) and DTR (Data Terminal Ready)
 * that we set both to 1. We don't enable interupts because we won't handle any
 * received data.
 *
 * com : The COM port to configure
 * */

void serial_configure_modem(unsigned short com);

/* serial_write
 * Write data into a specific serial port
 *
 * com : The COM port
 * buf : data to write to the serial port
 * len : number of characters to send to serial port
 * return - number of characters written
 * */

int serial_write(unsigned short com, char *buf, unsigned int len);

#endif // SERIAL_H
