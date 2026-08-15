
void kmain() {
  volatile unsigned short *vga = (unsigned short *)0xB8000;
  vga[0] = 'H' | (0x07 << 8);
}
