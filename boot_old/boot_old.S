#define ASM_FILE
#include <multiboot2.h>


		.text
		.globl start, _start
start:
_start:
		jmp multiboot_entry

		/* Align 64 bits boundary. */
		.align 8

		/* Multiboot header. */
multiboot_header:

		/* magic */
		.long MULTIBOOT2_HEADER_MAGIC
		/* ISA: i386 */
		.long MULTIBOOT_ARCHITECTURE_I386
		/* Header length. */
		.long multiboot_header_end - multiboot_header
		/* checksum */
		.long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header))


#ifndef __ELF__
address_tag_start:
		.short MULTIBOOT_HEADER_TAG_ADDRESS
		.short MULTIBOOT_HEADER_TAG_OPTIONAL
		.long address_tag_end - address_tag_start
		/* header addr */
		.long multiboot_header
		/* load addr */
		.long _start
		/* load end addr */
		.long _edata
		/* bss end addr */
		.long _end
address_tag_end:

entry_address_tag_start:
		.short MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
		.short MULTIBOOT_HEADER_TAG_OPTIONAL
		.long entry_address_tag_end - entry_address_tag_start
		/* entry addr */
		.long multiboot_entry
entry_address_tag_end:
#endif /* ELF */

framebuffer_tag_start:
		.short MULTIBOOT_HEADER_TAG_FRAMEBUFFER
		.short MULTIBOOT_HEADER_TAG_OPTIONAL
		.long framebuffer_tag_end - framebuffer_tag_start
		.long 1024
		.long 768
		.long 32
framebuffer_tag_end:
		.short MULTIBOOT_HEADER_TAG_END
		.short 0
		.long 8
multiboot_header_end:

multiboot_entry:
		/* Initialize the stack pointer. */
stack_top:
		movl stack_top, %esp
		/* Reset EFLAGS. */
		pushl $0
		popf
		/* Push the pointer to the Multiboot information structure. */
		pushl %ebx
		/* Push the magic value. */
		pushl %eax
		/* Now enter the C main function... */
		call cmain
loop: 	
		jmp loop
