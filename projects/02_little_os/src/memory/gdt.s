global gdt_flush ; make the label setgdt available outside of this file 

gdt_flush:
  mov eax, [esp + 4]
  lgdt [eax]

  mov ax, 0x10 ; kernel data selector
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp 0x08:.flush_cs ;far jump reloads cs with kernel code selector

.flush_cs: 
  ret
