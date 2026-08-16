volatile short *vga = (short *)0xB8000;

int str_len(char *str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

void print(char *msg) {
  int length = str_len(msg);
  int cur_pos = 0;
  for (int i = cur_pos; i < length; i++) {
    vga[i] = msg[i] | (0x07 << 8);
  }
}

void kmain() {
  print("Bye World");
  print("Haii");
}
