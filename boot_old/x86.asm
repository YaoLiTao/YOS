[SECTION .text]

GLOBAL in_byte
GLOBAL _insl

GLOBAL out_byte
GLOBAL _outsl

GLOBAL _stosb

;uchar in_byte(ushort port)
in_byte:
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
out_byte:
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