#include <stdint.h>
#include "drivers/header/print.h"
#include "drivers/header/time.h"
#include "drivers/header/gdt.h"
#include "drivers/header/idt.h"

void kmain(uint32_t *info_ptr) {
  // struct IDT_entry idt_entries[256];
  // struct IDTR idtr;
  // idtr.size = 8 * 256 - 1;
  // idtr.offset = (uint32_t)idt_entries;
  //__asm__ volatile("lidt [%0]" : : "r"(idtr));
  print("Hello Herbert");
}
