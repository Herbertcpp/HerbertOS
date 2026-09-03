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

void print_integer(int number) {
  int converted[1024];
  int totalDigits = 0;
  while(number > 0) {
    converted[totalDigits] = number % 10;
    number /= 10;

    totalDigits++;
  }
  char converted_str[totalDigits];
  for(int i = 0; i < totalDigits; i++) {
    converted_str[i] = '0' + converted[i];
  }
  print(converted_str);
}

uint8_t read_cmos_register(uint8_t reg) {
  uint8_t time = 0;
  __asm__(
    "out 0x70, %1\n"
    "in %0, 0x71\n"
    : "=a" (time)
    : "a"  (reg)
  );
  return time;
}

bool cmos_update_register() {
  uint8_t flag = 1;

  __asm__(
    "out 0x70, %1\n"
    "in %0, 0x71\n"
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

  for(;iteration_index < 7; iteration_index++) {

  uint8_t time = read_cmos_register(registers[iteration_index]);

  print(labels[iteration_index]);
  print(":");
  print_integer(time);
  print("\n");
  }
}

void kmain(uint32_t *info_ptr) {
  readTime();
}
