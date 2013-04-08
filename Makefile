CC = clang
CFLAGS = -Wall -Wextra -nostdlib -fno-builtin
CFLAGS += -Iinclude/
OBJECTS = loader.o kernel.o console.o libc.o mm.o

build: $(OBJECTS)
	ld -T linker.ld -o kernel.bin $(OBJECTS)

loader.o: loader.s
	nasm -f elf -o loader.o loader.s

run: build
	qemu -nographic -curses -monitor stdio -kernel kernel.bin

clean:
	rm -f *.o kernel.bin
