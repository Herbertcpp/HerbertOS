extern kmain

section .multiboot
  ALIGN 4
  dd 0x1BADB002
  dd 0
  dd -(0x1BADB002 + 0)

section .bss
  ALIGN 16
  stack_bottom:
    resb 16384
  stack_top:

section .text
  global start
  start:
    mov esp, stack_top
 
   call kmain

   cli
   hlt
