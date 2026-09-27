#include <stdint.h>

struct IDT_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

struct IDT {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t gate_type_etc;
    uint16_t offset_high;
} __attribute__((packed));

void loadIDT();
