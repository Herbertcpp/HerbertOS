clear
make os.iso
make clean
qemu-system-i386 \
-cdrom os.iso \
-rtc base=localtime \
-no-reboot \
-no-shutdown \
-d int,cpu_reset \
-D qemu.log \
-serial mon:stdio
