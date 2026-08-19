#define col 80
#include <stdint.h>

volatile short *vga = (short *)0xB8000;

int str_len(char *str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

void print(char *msg) {
  static int current_pos = 0;
  int pos = 0;
  while (msg[pos] != '\0') {
    if (msg[pos] != '\n') {
      vga[current_pos] = msg[pos] | (0x07 << 8);
      current_pos++;
      pos++;
    }

    if (msg[pos] == '\n') {
      int row = current_pos / col;
      int total = ++row * col;
      int rem = total - current_pos;

      for (int i = 0; i < rem; i++) {
        vga[current_pos] = ' ' | (0x07 << 8);
        current_pos++;
      }
      pos++;
    }
  }
}

struct framebuffer_info {
  uint32_t type;
  uint32_t size;
  uint64_t framebuffer_addr;
  uint32_t framebuffer_pitch;
  uint32_t framebuffer_width;
  uint32_t framebuffer_height;
  uint8_t framebuffer_bpp;
  uint8_t framebuffer_type;
  uint8_t reserved;
};

typedef struct info {
  uint32_t type;
  uint32_t size;
};

typedef struct framebuffer {
  uint32_t type;
  uint32_t size;
  uint64_t *framebuffer_addr;
  uint32_t pitch;
  uint32_t width;
  uint32_t height;
  uint8_t bpp;
  uint8_t framebuffer_type;
  uint8_t reserved;
};

void kmain(uint32_t *info_ptr) {
  uint64_t *framebuff_addr;
  struct framebuffer *dummy;
  struct info *information;

  info_ptr += 2;

  while (1) {
    information = (struct info *)info_ptr;
    if (information->type == 8) {
      dummy = (struct framebuffer *)info_ptr;
      framebuff_addr = dummy->framebuffer_addr;
    }
    int size = information->size;
    (uint8_t *)info_ptr += size;
  }
}
