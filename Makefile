#######################
# Makefile for foobar #
#######################

# Programs, flags, etc.
ASM		= nasm
CC		= clang
LD		= ld
ASMFLAGS	= -f elf
INCLUDE 	= -I include/
CFLAGS		= -m32 -fno-builtin -c
LDFLAGS		= -s -m elf_i386
LDTTEXT 	= -Ttext

# Some macro
TTEXT_KERNEL_NUM = 0x30400

# This Program
KERNEL		= bin/kernel
KERNEL_OBJS	= kernel/kernel.o boot/boot.o lib/x86.o \
			  lib/string.o kernel/interrupt.o kernel/protect.o

# All Phony Targets
.PHONY : everything final clean realclean all

# Default starting position
everything : $(KERNEL)

all : realclean everything

final : all clean

clean :
	rm -f $(KERNEL_OBJS)

realclean :
	rm -f $(KERNEL_OBJS) $(KERNEL)

cp :
	./losetup.sh
	cp /home/yao/yos/bin/kernel /mnt/boot/
	./dwsetup.sh
	objdump -D bin/kernel > kernel.txt

$(KERNEL) : $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) $(LDTTEXT) $(TTEXT_KERNEL_NUM) -o $(KERNEL) $(KERNEL_OBJS)

boot/boot.o : boot/boot.S
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

kernel/kernel.o : kernel/kernel.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

lib/x86.o : lib/x86.asm
	$(ASM) $(ASMFLAGS) $(INCLUDE) -o $@ $<

lib/string.o : lib/string.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

kernel/interrupt.o : kernel/interrupt.asm
	$(ASM) $(ASMFLAGS) $(INCLUDE) -o $@ $<

kernel/protect.o : kernel/protect.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<