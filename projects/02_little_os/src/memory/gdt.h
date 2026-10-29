#pragma once
#include "../lib/stdint.h"

#define GDT_ENTRIES 5

// try to mess around by reorder this struct
typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access_byte;
  uint8_t granularity; // flags | limit_middle
  uint8_t base_high;

} __attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t size;
  uint64_t base;
} __attribute__((packed)) gdt_ptr_t;

/* init_gdt
 * Initialize the GDT table
 *
 * */
void gdt_init();

/* set_gdt_gate
 * Set up the gdt entry
 *
 * i : the entry index
 * base : linear address where the segment begins
 * limit : maximum addressable unit
 * access : set up the permissions to access the
 * gran : for granularity flags
 * */
void gdt_set_entry(uint32_t i, uint32_t base, uint32_t limit, uint8_t access,
                   uint8_t gran);
