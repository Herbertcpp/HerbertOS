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

void print_integer(int n) {
  char buffer[20];
  int i = 0;

  if(n < 0) {
    print("-");
    n = -n;
  }
  if(n == 0) {
    print("0");
    return;
  }

  while(n > 0) {
    buffer[i++] = '0' + (n%10);
    n /= 10;
  }
  buffer[i] = '\0';
  int start = 0;
  int end = i - 1;
  while(start < end) {
    char temp = buffer[end];
    buffer[end] = buffer[start];
    buffer[start] = temp;
    start++;
    end--;
  }
  print(buffer);
}

uint8_t read_cmos_register(uint8_t reg) {
  uint8_t time = 0;
  __asm__ volatile (
    "out 0x70, %b1\n"
    "in %b0, 0x71\n"
    : "=a" (time)
    : "a"  (reg | 0x080)
  );
  return time;
}

uint8_t bcd_to_decimal(uint8_t bcd_number) {
  return ((bcd_number >> 4) * 10) + (bcd_number & 0x0F);
}

bool cmos_update_register() {
  uint8_t flag = 1;

  __asm__ volatile (
    "out 0x70, %b1\n"
    "in %b0, 0x71\n"
    : "=a" (flag)
    : "a"  ((uint8_t)0x8A)
  );
  return (flag & 0x80);
}

void readTime() {
  uint8_t iteration_index = 0;
  static char* labels[7] = {
    "seconds",
    "Minutes",
    "Hours",
    "Day of Week",
    "Day of Month",
    "Month",
    "Year",
  };
  static uint8_t registers[7] = {
    0x00,
    0x02,
    0x04,
    0x06,
    0x07,
    0x08,
    0x09,
  };

  do {} while(cmos_update_register());

  int raw_values[7];
  for(;iteration_index < 7; iteration_index++) {

  raw_values[iteration_index] = read_cmos_register(registers[iteration_index]);
  }
  uint8_t status_b = read_cmos_register(0x0B);
  bool binary = (status_b & 0x04);
  for(int i = 0; i < 7; i++) {
  int time = raw_values[i];

  if(!binary) {
      time = bcd_to_decimal(time);
    }

  print(labels[i]);
  print(":");
  print_integer(time);
  print("\n");
  }
}

struct IDT_entry {
  uint16_t offset_low;
  uint32_t segment_selector;
  uint8_t reserved;
  uint8_t attributes;
  uint16_t offset_high;
} __attribute__((packed));

struct IDTR {
  uint16_t size;
  uint32_t offset;
};

void kmain(uint32_t *info_ptr) {
  struct IDT_entry idt_entries[256];
  struct IDTR idtr;
  idtr.size = 8 * 256 - 1;
  idtr.offset = (uint32_t)idt_entries;
  __asm__ volatile (
    "lidt [%0]"
    :
    : "r" (idtr)
  );
}
