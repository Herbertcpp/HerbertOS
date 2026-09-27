#include <stdint.h>
#include "io.h"

void outb(uint8_t byte, uint16_t reg) {
    __asm__ volatile ("outb %0, %1" : : "m" (byte), "m" (reg));
}
