#include "../header/idt.h"
#include "../header/print.h"
#include "../header/pic.h"
#include <stdint.h>
#include <stdbool.h>

extern void* isr_stub_table[];

static  idt_entry_t idt[256];
static  idtr_t idtr;
bool caps_lock_active = false;
bool shift_pressed = false;

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

void keyboard_handler(void) {
    uint8_t scancode = inb(0x60);


    static const char set1[128] = {
        0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
             '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
             0,  'a','s','d','f','g','h','j','k','l',';','\'','`',
             0,  '\\','z','x','c','v','b','n','m',',','.','/', 0, 0, 0, ' ', '*',
    };
    static const char set1_caps[128] = {
        0, 27, 0,'2','3','4','5','6','7','8','9','0','-','=', '\b',
             '\t','Q','W','E','R','T','Y','U','I','O','P','[',']','\n',
             0,  'A','S','D','F','G','H','J','K','L',';','\'','`',
             0,  '\\','Z','X','C','V','V','N','M',',','.','/', 0, 0, 0, 0,
    };

    char key[2] = { set1[scancode ], '\0'};
    if(scancode == 0x2A) {
        shift_pressed = true;
        outb(0x20, 0x20);
        return;
    }
    if(scancode == 0xAA) {
        shift_pressed = false;
        outb(0x20, 0x20);
        return;
    }
    if(scancode > 0x43) {
        outb(0x20, 0x20);
        return;
    }
    if(key[0] == '*') {
        caps_lock_active = !caps_lock_active;
    }
    if(caps_lock_active || shift_pressed) {
        char key[2] = {set1_caps[scancode], '\0'};
        print(key);
    } else {
    print(key);
    }

    outb(0x20, 0x20);
}

void initIDT() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = sizeof(idt) - 1;

    for(int i = 0; i < 34; i++) {
        idt_set_descriptor(i, isr_stub_table[i],  0x8E);
    }
    __asm__ volatile ("lidt %0" : : "m" (idtr));
    __asm__ volatile ("sti");
}
