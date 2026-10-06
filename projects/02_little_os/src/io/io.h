#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/* outb:
 * Sends the given data to the given I/O port. Defined in io.s
 *
 * port : The I/O port to send the data
 * data : The data to send to the I/O port
 * */

void outb(unsigned short port, unsigned char data);

/* inb:
 * Read a byte from an I/O port
 *
 * port : the address of the I/O port
 * return - The read type
 * */

unsigned char inb(unsigned short port);

#endif // INCLUDE_IO_H
