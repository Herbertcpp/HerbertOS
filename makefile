boot.o : kernel/i686/boot.asm
	nasm -f elf32 kernel/i686/boot.asm -o boot.o

kernel.o : kernel/kernel.c
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/kernel.c -o kernel.o
print.o : kernel/drivers/source/print.c
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/source/print.c -o print.o
time.o : kernel/drivers/source/time.c
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/source/time.c -o time.o
gdt.o : kernel/drivers/header/gdt.h
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/source/gdt.c -o gdt.o

idt.o : kernel/drivers/header/idt.h
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/source/idt.c -o idt.o

os : boot.o kernel.o print.o time.o gdt.o idt.o
	i686-elf-gcc -T linker.ld -o os -ffreestanding -nostdlib boot.o kernel.o print.o time.o gdt.o idt.o

os.iso : os
	cp os isodir/boot/os
	grub2-mkrescue -o os.iso isodir

clean :
	rm -rf *.o
