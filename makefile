build:
	nasm -f elf32 boot.asm -o boot.o
	i686-elf-gcc -c -ffreestanding kernel.c -o kernel.o
	i686-elf-gcc -T linker.ld -o os -ffreestanding -nostdlib boot.o kernel.o 
	cp os isodir/boot/myos
	grub-mkrescue -o os.iso isodir
	qemu-system-i386 -cdrom os.iso
