#include <stdbool.h>
#include <stdint.h>
#include "../header/print.h"

uint8_t read_cmos_register(uint8_t reg) {
  uint8_t time = 0;
  __asm__ volatile("out 0x70, %b1\n"
                   "in %b0, 0x71\n"
                   : "=a"(time)
                   : "a"(reg | 0x080));
  return time;
}

uint8_t bcd_to_decimal(uint8_t bcd_number) {
  return ((bcd_number >> 4) * 10) + (bcd_number & 0x0F);
}

bool cmos_update_register() {
  uint8_t flag = 1;

  __asm__ volatile(";out 0x70, %b1\n"
                   "in %b0, 0x71\n"
                   : "=a"(flag)
                   : "a"((uint8_t)0x8A));
  return (flag & 0x80);
}

void readTime() {
  uint8_t iteration_index = 0;
  static char *labels[7] = {
      "seconds",      "Minutes", "Hours", "Day of Week",
      "Day of Month", "Month",   "Year",
  };
  static uint8_t registers[7] = {
      0x00, 0x02, 0x04, 0x06, 0x07, 0x08, 0x09,
  };

  do {
  } while (cmos_update_register());

  int raw_values[7];
  for (; iteration_index < 7; iteration_index++) {

    raw_values[iteration_index] =
        read_cmos_register(registers[iteration_index]);
  }
  uint8_t status_b = read_cmos_register(0x0B);
  bool binary = (status_b & 0x04);
  for (int i = 0; i < 7; i++) {
    int time = raw_values[i];

    if (!binary) {
      time = bcd_to_decimal(time);
    }

    print(labels[i]);
    print(":");
    print_integer(time);
    print("\n");
  }
}
