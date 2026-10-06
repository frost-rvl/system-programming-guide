SOURCES_C = $(wildcard src/*/*.c src/*/*/*.c)
SOURCES_ASM = $(wildcard src/*/*.s)

OBJECTS_C = $(patsubst src/%.c,build/%.o,$(SOURCES_C))
OBJECTS_ASM = $(patsubst src/%.s,build/%_asm.o,$(SOURCES_ASM))
OBJECTS = $(OBJECTS_C) $(OBJECTS_ASM)

CC= gcc
CFLAGS= -DPUBLIC= -DPRIVATE=static -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
				-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LDFLAGS= -T link.ld -melf_i386
AS= nasm
ASFLAGS= -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o build/kernel.elf

little_os.iso: kernel.elf
	cp build/kernel.elf iso/boot/kernel.elf	
	genisoimage -R  \
		-b boot/grub/stage2_eltorito	\
		-no-emul-boot	\
		-boot-load-size 4	\
		-A little_os	\
		-input-charset utf8	\
		-quiet	\
		-boot-info-table	\
		-o little_os.iso	\
		iso

run: little_os.iso
	qemu-system-i386 -cdrom little_os.iso \
		-monitor stdio

serial: little_os.iso
	qemu-system-i386 -cdrom little_os.iso \
		-serial file:log

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

build/%_asm.o: src/%.s
	mkdir -p $(dir $@)
	$(AS)	$(ASFLAGS) $< -o $@

clean:
	rm -rf build/*.o build/kernel.elf little_os.iso
