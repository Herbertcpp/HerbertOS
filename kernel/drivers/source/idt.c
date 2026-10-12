#include "../header/idt.h"
#include <stdint.h>

struct idt_gate entries[256];

void setGate(int index, uint32_t offset, uint16_t segment, uint8_t attr) {
    entries[index].offset_low = offset & 0xFFFF;
    entries[index].offset_high = (offset >> 16) &0xFFFF;
    entries[index].segment_selector = segment;
    entries[index].attributes = attr;
}

void initIDT() {

}
