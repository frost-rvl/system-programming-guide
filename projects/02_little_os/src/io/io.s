global outb ; make the label outb visible outside this file
global inb

; outb - send a byte to an I/O port
; stack: [esp + 8] the data type
;        [esp + 4] the I/O port
;        [esp] return address
outb:
  mov al, [esp + 8] ;move the data to be sent into the al register 
  mov dx, [esp + 4] ;move the address of the I/O port into the dx register
  out dx, al ; send data to the I/O port
  ret

; inb - returns a byte from the given I/O port
;
inb:
  mov dx, [esp + 4] ; move the address of the I/O port the the dx register
  in al, dx ; read a byte from the I/O port and store it in the al register
  ret ; return the read byte
