#include <stdint.h>
#include "drivers/header/print.h"
#include "drivers/header/time.h"
#include "drivers/header/gdt.h"

void kmain(uint32_t *info_ptr) {
  print("Herbert\n");
  initGDT();
}
