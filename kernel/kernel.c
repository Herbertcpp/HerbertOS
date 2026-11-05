#include <stdint.h>
#include "drivers/header/print.h"
#include "drivers/header/time.h"
#include "drivers/header/gdt.h"
#include "drivers/header/pic.h"
#include "drivers/header/idt.h"
#include "drivers/header/paging.h"

void kmain(uint32_t *info_ptr) {
  print("I guess bro");
  initGDT();
  remap(0x20, 0x28);
  initIDT();
  initPaging();
  __asm__ volatile("sti");

  for(;;) {
      __asm__ volatile("hlt");
  }
}
