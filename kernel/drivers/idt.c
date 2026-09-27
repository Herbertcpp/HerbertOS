#include <stdint.h>
#include "print.h"
#include "idt.h"

void loadIDT() {
    struct IDT idt_entries[256];
    struct IDT_descriptor idtr;
    idtr.offset = (uint32_t)idt_entries;
    idtr.size = 8 * 256 - 1;

    __asm__ volatile("lidt %0" : : "m" (idtr));
}
