#include <stdint.h>
#include "drivers/header/print.h"
#include "drivers/header/time.h"
#include "drivers/header/gdt.h"
#include "drivers/header/pic.h"

void kmain(uint32_t *info_ptr) {
  initGDT();
  remap(0x20, 0x28);
}
