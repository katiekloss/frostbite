CC = clang
CFLAGS = -Wall -Wextra -nostdlib -fno-builtin
CFLAGS += -Iinclude/
OBJECTS = loader.o kernel.o console.o libc.o

iso: kernel
	mkdir -p iso/boot/grub
	cp menu.lst iso/boot/grub/
	cp /usr/lib/grub/i386-pc/stage2_eltorito iso/boot/grub/
	cp kernel.bin iso/boot/
	genisoimage -quiet -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o frostbite.iso iso/

kernel: $(OBJECTS)
	ld -T linker.ld -o kernel.bin $(OBJECTS)

loader.o: loader.s
	nasm -f elf -o loader.o loader.s

usb: kernel
	mkdir -p /media/usb/boot/grub
	cp menu.lst.usb /media/usb/boot/grub/menu.lst
	cp /usr/lib/grub/i386-pc/stage1 /media/usb/boot/grub/
	cp /usr/lib/grub/i386-pc/stage2 /media/usb/boot/grub/
	cp /usr/lib/grub/i386-pc/e2fs_stage1_5 /media/usb/boot/grub/
	grub-install --root-directory=/media/usb /dev/sdb
	cp kernel.bin /media/usb/boot/
clean:
	rm -Rf *.o kernel.bin iso/ frostbite.iso
