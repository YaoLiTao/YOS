[SECTION .text]

extern	exception_handler
extern  disp_IRQ

GLOBAL EOI

;默认中断
GLOBAL divide_error
GLOBAL single_step_exception
GLOBAL nmi
GLOBAL breakpoint_exception
GLOBAL overflow
GLOBAL bounds_check
GLOBAL inval_opcode
GLOBAL copr_not_available
GLOBAL double_fault
GLOBAL copr_seg_overrun
GLOBAL inval_tss
GLOBAL segment_not_present
GLOBAL stack_exception
GLOBAL general_protection
GLOBAL page_fault
GLOBAL copr_error
GLOBAL IRQ_00
GLOBAL IRQ_01
GLOBAL IRQ_02 ;不可用
GLOBAL IRQ_03
GLOBAL IRQ_04
GLOBAL IRQ_05
GLOBAL IRQ_06
GLOBAL IRQ_07
GLOBAL IRQ_08
GLOBAL IRQ_09
GLOBAL IRQ_10
GLOBAL IRQ_11
GLOBAL IRQ_12
GLOBAL IRQ_13
GLOBAL IRQ_14
GLOBAL IRQ_15



EOI:
	mov al, 20h
	out 20h, al
	nop
	nop
	nop
	nop
	ret

divide_error:
	push	0xFFFFFFFF	; no err code
	push	0		; vector_no	= 0
	jmp	exception
single_step_exception:
	push	0xFFFFFFFF	; no err code
	push	1		; vector_no	= 1
	jmp	exception
nmi:
	push	0xFFFFFFFF	; no err code
	push	2		; vector_no	= 2
	jmp	exception
breakpoint_exception:
	push	0xFFFFFFFF	; no err code
	push	3		; vector_no	= 3
	jmp	exception
overflow:
	push	0xFFFFFFFF	; no err code
	push	4		; vector_no	= 4
	jmp	exception
bounds_check:
	push	0xFFFFFFFF	; no err code
	push	5		; vector_no	= 5
	jmp	exception
inval_opcode:
	push	0xFFFFFFFF	; no err code
	push	6		; vector_no	= 6
	jmp	exception
copr_not_available:
	push	0xFFFFFFFF	; no err code
	push	7		; vector_no	= 7
	jmp	exception
double_fault:
	push	8		; vector_no	= 8
	jmp	exception
copr_seg_overrun:
	push	0xFFFFFFFF	; no err code
	push	9		; vector_no	= 9
	jmp	exception
inval_tss:
	push	10		; vector_no	= A
	jmp	exception
segment_not_present:
	push	11		; vector_no	= B
	jmp	exception
stack_exception:
	push	12		; vector_no	= C
	jmp	exception
general_protection:
	push	13		; vector_no	= D
	jmp	exception
page_fault:
	push	14		; vector_no	= E
	jmp	exception
copr_error:
	push	0xFFFFFFFF	; no err code
	push	16		; vector_no	= 10h
	jmp	exception

exception:
	call	exception_handler
	add	esp, 4*2	; 让栈顶指向 EIP，堆栈中从顶向下依次是：EIP、CS、EFLAGS
	hlt


IRQ_00:
	push 0
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_01:
	push 1
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_02:
	push 2
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_03:
	push 3
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_04:
	push 4
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_05:
	push 5
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_06:
	push 6
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_07:
	push 7
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_08:
	push 8
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_09:
	push 9
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_10:
	push 10
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_11:
	push 11
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_12:
	push 12
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_13:
	push 13
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_14:
	push 14
	call disp_IRQ
	add  esp, 4
	hlt
IRQ_15:
	push 15
	call disp_IRQ
	add  esp, 4
	hlt