clear
make os.iso
make clean
qemu-system-i386 -cdrom os.iso -rtc base=localtime
