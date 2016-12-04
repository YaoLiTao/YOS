;org 07c00h

%include "pm.inc"

EXTERN bootmain
GLOBAL LABEL_START

;	jmp short LABEL_START
;	nop

;%include "fat12hdr.inc"

[SECTION .s16]
[BITS 16]
LABEL_START:
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax

; 加载 GDTR
	lgdt	[GdtPtr]

; 关中断
	cli

; 打开地址线A20
	in	al, 92h
	or	al, 00000010b
	out	92h, al

; 准备切换到保护模式
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax

; 跳转到保护模式
	jmp dword SelectorCode32:LABEL_START_32

;END OF [SECTION .s16]

[SECTION .s32]
[BITS 32]
LABEL_START_32:
	mov ax, SelectorData
	mov ds, ax
	mov es, ax
	mov ss, ax

	xor eax, eax
	mov fs, ax
	mov ax, SelectorVideo
	mov gs, ax

	xor eax, eax
	mov eax, 0x7c00
	mov esp, eax
	call bootmain

;	调用失败
	mov ax, 0x8a00
	mov dx, ax
	out dx, ax
	mov ax, 0x8ae0
	out dx, ax

spin:
	jmp spin

;END OF [SECTION .s32]

[SECTION .gdt]
LABEL_GDT:				Descriptor			0,			0, 			0
LABEL_DESC_CODE32:		Descriptor			0, 0xffffffff,		DA_CR  |  DA_32		;存在的可执行可读代码段属性值
LABEL_DESC_DATA:		Descriptor			0, 0xffffffff, 		DA_DRW |  DA_32		;存在的可读写数据段属性值
LABEL_DESC_VIDEO 		Descriptor	  0B8000h, 	   0FFFFh, 		DA_DRW				;存在的可读写数据段属性值

GdtLen equ $ - LABEL_GDT
GdtPtr dw GdtLen - 1
	   dd LABEL_GDT

SelectorCode32 equ LABEL_DESC_CODE32 - LABEL_GDT
SelectorData   equ LABEL_DESC_DATA 	 - LABEL_GDT
SelectorVideo  equ LABEL_DESC_VIDEO  - LABEL_GDT

;END OF [SECTION .gdt]