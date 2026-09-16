boot.o : kernel/i686/boot.asm
	nasm -f elf32 kernel/i686/boot.asm -o boot.o

kernel.o : kernel/kernel.c
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/kernel.c -o kernel.o
print.o : kernel/drivers/print.c
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/print.c -o print.o
time.o : kernel/drivers/time.c
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/time.c -o time.o
gdt.o : kernel/drivers/gdt.h
	i686-elf-gcc -masm=intel -c -ffreestanding kernel/drivers/gdt.c -o gdt.o


os : boot.o kernel.o print.o time.o gdt.o
	i686-elf-gcc -T linker.ld -o os -ffreestanding -nostdlib boot.o kernel.o print.o time.o gdt.o

os.iso : os
	cp os isodir/boot/os
	grub-mkrescue -o os.iso isodir

clean :
	rm -rf *.o
