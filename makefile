boot.o : i686/boot.asm
	nasm -f elf32 i686/boot.asm -o boot.o

kernel.o : kernel/kernel.c
	i686-elf-gcc -c -ffreestanding kernel/kernel.c -o kernel.o

os : boot.o kernel.o
	i686-elf-gcc -T linker.ld -o os -ffreestanding -nostdlib boot.o kernel.o 

os.iso : os
	cp os isodir/boot/os
	grub-mkrescue -o os.iso isodir
