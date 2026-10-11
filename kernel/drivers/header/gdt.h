// Notes: LGDT asm instruction to load the GDT Descriptor (GDTR)
// GDT pointed to by GDTR

#include <stdint.h>

/*
struct GDT_entry {
   uint16_t limit;
   uint16_t base_low;
   uint8_t base_mid;
   uint8_t access_byte;
   uint8_t limit_flags;
   uint8_t base_high;
}__attribute__((packed));

struct GDTR {
    uint16_t size;
    uint32_t* addr;
}__attribute__((packed));

void loadGDT();

void fillGDTEntry(uint8_t *source, uint8_t access_bytes, uint8_t flags);

void nullDescriptor(uint8_t* source);
*/

void initGDT();