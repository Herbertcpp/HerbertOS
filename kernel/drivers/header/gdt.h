// Notes: LGDT asm instruction to load the GDT Descriptor (GDTR)
// GDT pointed to by GDTR

#include <stdint.h>

struct GDTR {
    uint16_t size;   // size of table - 1
    uint32_t offset; //Linear adress of gdt (paging included or smth)
}__attribute__((packed));

struct GDT_entry {
    uint16_t limit_1;
    uint16_t base_1;
    uint8_t base_2;
    uint8_t access_bytes;
    uint8_t flags_limit;
    uint8_t base_3;
}__attribute__((packed));

void loadGDT();
