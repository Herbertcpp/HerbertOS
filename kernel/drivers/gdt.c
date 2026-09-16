#include "gdt.h"
#include <stdint.h>

void loadGDT() {
    struct GDT_entry gdt[3];
    gdt[0] = (struct GDT_entry){0};
    struct GDTR gdtr;
    gdtr.size = sizeof(gdtr) - 1;
    gdtr.offset = (uint32_t)&gdt;

    gdt[1]  = (struct GDT_entry) {
        0xFF,
        0,
        0,
        0x92,
        0xC0,
        0
    };

    gdt[2] = (struct GDT_entry) {
       0xFF,
       0,
       0,
       0x92,
       0xC0,
       0
    };

    __asm__ volatile(
        "cli\n"
        "lgdt %0"
        :
        : "m" (&gdt)
    );
}
