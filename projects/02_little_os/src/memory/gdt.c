#include "gdt.h"

extern void gdt_flush(gdt_ptr_t *);

PRIVATE gdt_entry_t gdt_entries[GDT_ENTRIES];
PRIVATE gdt_ptr_t gdt_ptr;

PUBLIC void gdt_set_entry(uint32_t i, uint32_t base, uint32_t limit,
                          uint8_t access, uint8_t gran) {
  gdt_entries[i].base_low = base & 0xFFFF;
  gdt_entries[i].base_middle = (base >> 16) & 0xFF;
  gdt_entries[i].base_high = (base >> 24) & 0xFF;
  gdt_entries[i].limit_low = limit & 0xFFFF;
  gdt_entries[i].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
  gdt_entries[i].access_byte = access;
}

PUBLIC void gdt_init() {
  gdt_ptr.size = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
  gdt_ptr.base = (uint32_t)&gdt_entries;

  gdt_set_entry(0, 0, 0, 0, 0); // null segment
  // ring 0
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xC0); // kernel code segment
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xC0); // kernel data segment
  // ring 3 ( not used for now )
  gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xC0); // user code segment
  gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xC0); // user data segment

  // 0x9A = 1001 1010
  // 0x92 = 1001 0010
  // 0xFA = 1111 1010
  // 0xF2 = 1111 0010
  // 0xC0 = 1100 0000
  gdt_flush(&gdt_ptr);
}
