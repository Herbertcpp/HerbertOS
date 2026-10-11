#include <stdint.h>
#include "../header/gdt.h"
#include "../header/print.h"

extern void loadGDT();

/*

void fillGDTEntry(uint8_t *source, uint8_t access_bytes, uint8_t flags) {

    for(int i = 0; i < 8; i++) {
        source[i] = 0x00;
    }

    source[0] =  limit & 0xFF;
    source[1] =  (limit >> 8) & 0xFF;
    source[6] =  (limit >>16) & 0x0F;
   source[0] = 0xFF;
   source[1] = 0xFF;

    source[5] = access_bytes & 0xF;

    source[6] = (flags << 4) | 0x0F;
}

void nullDescriptor(uint8_t* source) {
    for(int i =0; i < 8; i++) {
        source[i] = 0x00;
    }
}

void loadGDT() {
    struct GDT_entry gdts[3];
    struct GDTR gdtr;
    nullDescriptor((uint8_t*)&gdts[0]);
    fillGDTEntry((uint8_t*)&gdts[1], 0x9B, 0xC);
    fillGDTEntry((uint8_t*)&gdts[2], 0xAB, 0xC);
    gdtr.size = 23;
    gdtr.addr = (uint32_t*)&gdts;

    __asm__ volatile("lgdt %0" : : "m" (gdtr));
    reloadSegments();
}
*/

void initGDT() {
    loadGDT();
    print("Loaded GDT");
}