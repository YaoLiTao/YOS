[SECTION .text]
[BITS 32]

GLOBAL _in_byte
GLOBAL _insl
GLOBAL _out_byte
GLOBAL _outsl
GLOBAL _stosb
GLOBAL _lgdt
GLOBAL _lidt
GLOBAL _putc
GLOBAL _sti
GLOBAL _cli
GLOBAL _ud

;uchar in_byte(ushort port)
_in_byte:
	xor eax, eax
	mov edx, [esp + 4]	 ; edx << ushort port
	in al, dx			 ; 返回值由eax传递
	nop
	nop
	ret

;void _insl(int port, void* addr, int count)
_insl:
	push ebp
	mov ebp, esp

	pushfd
	push edi

	mov edx, [ebp + 8]	; edx << int port
	mov eax, [ebp + 12] ; edi << void* addr
	mov edi, eax
	mov ecx, [ebp + 16] ; ecx << int count

	cld
	rep insd

	pop edi
	popfd

	mov esp, ebp
	pop ebp
	ret

;void out_byte(ushort port, uchar data)
_out_byte:
	mov edx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	nop
	nop
	ret

;void _stosb(void *addr, int data, int count)
_stosb:
	push ebp
	mov ebp, esp

	pushfd
	push edi

	xor eax, eax
	mov eax, [ebp + 8]	; edi << void *addr
	mov edi, eax
	mov eax, [ebp + 12]
	mov ecx, [ebp + 16]

	cld
	rep stosb

	pop edi
	popfd

	mov esp, ebp
	pop ebp
	ret

;void _lgdt(GdtPtr *p)
_lgdt:
	push ebp
	mov ebp, esp

	pushfd

	mov eax, [ebp + 8]
	lgdt [eax]

	jmp dword 8:newseg ;长跳转把选择子导入CS, 8 = (1 << 3)代表了选择子1:SELECTOR_CODE
newseg:
	xor eax, eax
	mov fs, ax
	mov ax, 16 ;16 = (2 << 3)代表了选择子2:SELECTOR_DATA
	mov ds, ax
	mov es, ax
	mov ss, ax
	xor eax, eax
	mov ax, 24 ;24 = (3 << 3)代表了选择子3:SELECTOR_GS
	mov gs, ax

	popfd

	mov esp, ebp
	pop ebp
	ret

;void _putc(int pos, int char_and_attr)
_putc:
	push ebp
	mov ebp, esp

	pushfd
	
	xor eax, eax
	mov edi, [ebp + 8]
	mov eax, [ebp + 12]
	mov [gs:edi], eax

	popfd

	mov esp, ebp
	pop ebp
	ret
	 

_lidt:
	push ebp
	mov ebp, esp

	pushfd
	
	mov eax, [ebp + 8]
	lidt [eax]

	popfd

	mov esp, ebp
	pop ebp
	ret

_sti:
	sti
	ret

_cli:
	cli
	ret

_ud:
	ud2
	ret
