extern kmain

section .multiboot
  ALIGN 8
  header_start:
  dd 0xE85250D6 
  dd 0
  dd header_end - header_start
  dd -(0xE85250D6 + 0 + (header_end - header_start))
  dw 5 ;type
  dw 0;flags
  dd 20 ;size
  dd 0
  dd 0
  dd 32

  dd 0

  dw 0
  dw 0
  dd 8

  header_end:

section .bss
  ALIGN 16
  stack_bottom:
    resb 16384
  stack_top:

section .text
  global start
  start:
   mov esp, stack_top
   push ebx
   call kmain

   cli
   hlt
