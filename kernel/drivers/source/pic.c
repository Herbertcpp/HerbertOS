#include <stdint.h>
#define pic1_command 0x20
#define pic1_data 0x21
#define pic2_command 0xA0
#define pic2_data 0xA1

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a" (val), "Nd" (port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

void io_wait() {
    outb(0x80, 0);
}

void remap(int offset1, int offset2) {
    //0x11 initialization command
    outb(pic1_command, 0x11);
    io_wait();
    outb(pic2_command, 0x11);
    io_wait();
    //Master / Slave offsets
    outb(pic1_data, offset1);
    io_wait();
    outb(pic2_data, offset2);

    io_wait();
    outb(pic1_data, 0x4);
    io_wait();
    outb(pic2_data, 0x2);
    io_wait();

    outb(pic1_data, 0x01);
    io_wait();
    outb(pic2_data, 0x01);
    io_wait();

    outb(pic1_data, 0);
    outb(pic2_data, 0);
}
