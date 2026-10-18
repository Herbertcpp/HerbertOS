#include "../header/idt.h"
#include "../header/print.h"
#include <stdint.h>

extern void* isr_stub_table[];

static  idt_entry_t idt[256];
static  idtr_t idtr;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void exception_handler(void) {
    print("Interrupt encountered");
    volatile uint16_t* vga = (volatile uint16_t*)0xB8000;
    //vga[0] = 0x4F00 | 'L';
    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}

void initIDT() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * 255 - 1;

    for(int i = 0; i < 32; i++) {
        idt_set_descriptor(i, isr_stub_table[i],  0x8E);
    }
    __asm__ volatile ("lidt %0" : : "m" (idtr));
    __asm__ volatile ("sti");
}
