CC      := i686-elf-gcc
CFLAGS  := -masm=intel -ffreestanding
OBJS    := boot.o kernel.o print.o time.o gdt.o asm_gdt.o idt.o pic.o isr.o

os : $(OBJS)
	$(CC) -T linker.ld -o os -ffreestanding -nostdlib $(OBJS)

os.iso : os
	cp os isodir/boot/os
	grub-mkrescue -o os.iso isodir

boot.o : kernel/i686/boot.asm
	nasm -f elf32 kernel/i686/boot.asm -o boot.o

asm_gdt.o : kernel/drivers/asm/gdt.asm
	nasm -f elf32 kernel/drivers/asm/gdt.asm -o asm_gdt.o

isr.o : kernel/drivers/asm/isr.asm
	nasm -f elf32 kernel/drivers/asm/isr.asm -o isr.o

kernel.o : kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

print.o : kernel/drivers/source/print.c
	$(CC) $(CFLAGS) -c kernel/drivers/source/print.c -o print.o

time.o : kernel/drivers/source/time.c
	$(CC) $(CFLAGS) -c kernel/drivers/source/time.c -o time.o

gdt.o : kernel/drivers/source/gdt.c kernel/drivers/header/gdt.h
	$(CC) $(CFLAGS) -c kernel/drivers/source/gdt.c -o gdt.o

idt.o : kernel/drivers/source/idt.c kernel/drivers/header/idt.h
	$(CC) $(CFLAGS) -c kernel/drivers/source/idt.c -o idt.o

pic.o : kernel/drivers/source/pic.c kernel/drivers/header/pic.h
	$(CC) $(CFLAGS) -c kernel/drivers/source/pic.c -o pic.o

clean :
	rm -rf *.o
