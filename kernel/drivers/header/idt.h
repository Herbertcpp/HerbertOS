#include <stdint.h>

struct idt_gate {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t offset_high;
}__attribute__((packed));

struct idtr {
    uint16_t size;
    uint32_t base;
}__attribute__((packed));

void setGate(int index, uint32_t offset, uint16_t segment, uint8_t attr);

void initIDT();