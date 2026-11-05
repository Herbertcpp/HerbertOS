#include <stdint.h>
#include "../header/paging.h"
#include "../header/print.h"

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();
void initPaging() {
//Found some cool new syntax on attributes using gcc whilst looking through the docs
[[gnu::aligned(4096)]] int page_dir[1024];
[[gnu::aligned(4096)]] int page_table[1024];

for(int i = 0; i < 1024; i++) {
    page_dir[i] = 0x00000002;
    }

for(int i = 0; i < 1024; i++) {
    page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
    }

page_dir[0] =  ((unsigned int)page_table) | 3;
    print("starting to enable paging");
    loadPageDirectory(page_dir);
    enablePaging();
    print("Paging works?");
}
