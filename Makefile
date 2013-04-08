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

clean:
	rm -Rf *.o kernel.bin iso/ frostbite.iso
