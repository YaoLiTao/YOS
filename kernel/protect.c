#ifndef _YOS_PROTECT_
#define _YOS_PROTECT_ 1

#include <type.h>
#include <protect.h>

#endif


void init_descriptor(Descriptor *desc, uint base, uint limit, ushort attribute) {
	desc->limit_low = (ushort)(limit & 0x0ffff);
	desc->base_low = (ushort)(base & 0x0ffff);
	desc->base_mid = (uchar)((base >> 16) & 0x0ff);
	desc->attr1 = (uchar)(attribute & 0x0FF);
	desc->limit_high_attr2 = (uchar)((limit >> 16) & 0x00f) | ((attribute >> 8) & 0x0f0);
	desc->base_high = (uchar)(base >> 24) & 0x0FF;
}

void init_gate(Gate *gate, ushort sel, uint offset, uchar dc, uchar attribute){
	gate->offset_low = (ushort)(offset & 0x0ffff);
	gate->selector = sel;
	gate->dcount = dc;
	gate->attr = attribute;
	gate->offset_high = (ushort)((offset >> 16) & 0x0ffff);
}

void suspend(){
	ssp:
		goto ssp;
}

void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags){
	char * err_msg[] = {"#DE Divide Error",
			    "#DB RESERVED",
			    "—  NMI Interrupt",
			    "#BP Breakpoint",
			    "#OF Overflow",
			    "#BR BOUND Range Exceeded",
			    "#UD Invalid Opcode (Undefined Opcode)",
			    "#NM Device Not Available (No Math Coprocessor)",
			    "#DF Double Fault",
			    "    Coprocessor Segment Overrun (reserved)",
			    "#TS Invalid TSS",
			    "#NP Segment Not Present",
			    "#SS Stack-Segment Fault",
			    "#GP General Protection",
			    "#PF Page Fault",
			    "—  (Intel reserved. Do not use.)",
			    "#MF x87 FPU Floating-Point Error (Math Fault)",
			    "#AC Alignment Check",
			    "#MC Machine Check",
			    "#XF SIMD Floating-Point Exception"
	};
	printf("Exception no:%x  MSG:%s\nEFLAGS:%x  CS:%x  EIP:%x  Error code:%x\n", vec_no, err_msg[vec_no], eflags, cs, eip, err_code);
}

void disp_IRQ(int irq){
	printf("IRQ:%d\n", irq);
}