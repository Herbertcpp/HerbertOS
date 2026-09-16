#include "print.h"

#define col 80

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

  if (n < 0) {
    print("-");
    n = -n;
  }
  if (n == 0) {
    print("0");
    return;
  }

  while (n > 0) {
    buffer[i++] = '0' + (n % 10);
    n /= 10;
  }
  buffer[i] = '\0';
  int start = 0;
  int end = i - 1;
  while (start < end) {
    char temp = buffer[end];
    buffer[end] = buffer[start];
    buffer[start] = temp;
    start++;
    end--;
  }
  print(buffer);
}
