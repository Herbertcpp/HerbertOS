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
  while (current_pos <= current_pos + str_len(msg) & msg[pos] != '\0') {
    vga[current_pos] = msg[pos] | (0x07 << 8);
    current_pos++;
    pos++;
  }
}

void kmain() {
  print("Bye World\n");
  print("Haii");
}
