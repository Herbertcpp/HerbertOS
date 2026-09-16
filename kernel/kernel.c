#include <stdint.h>
#include "drivers/print.h"
#include "drivers/time.h"
#include "drivers/gdt.h"

void kmain(uint32_t *info_ptr) {
  // struct IDT_entry idt_entries[256];
  // struct IDTR idtr;
  // idtr.size = 8 * 256 - 1;
  // idtr.offset = (uint32_t)idt_entries;
  //__asm__ volatile("lidt [%0]" : : "r"(idtr));
  print("HerbertOS");

  loadGDT();
}
