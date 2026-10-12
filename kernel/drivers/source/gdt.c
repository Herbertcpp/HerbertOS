#include <stdint.h>
#include "../header/gdt.h"
#include "../header/print.h"

extern void loadGDT();

void initGDT() {
    loadGDT();
    print("Loaded GDT");
}