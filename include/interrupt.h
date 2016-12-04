#ifndef _YOS_INTERRUPT_H_
#define _YOS_INTERRUPT_H_ 1

#include <type.h>

void EOI();

//默认中断
void divide_error();
void single_step_exception();
void nmi();
void breakpoint_exception();
void overflow();
void bounds_check();
void inval_opcode();
void copr_not_available();
void double_fault();
void copr_seg_overrun();
void inval_tss();
void segment_not_present();
void stack_exception();
void general_protection();
void page_fault();
void copr_error();
void IRQ_00();
void IRQ_01();
void IRQ_02();
void IRQ_03();
void IRQ_04();
void IRQ_05();
void IRQ_06();
void IRQ_07();
void IRQ_08();
void IRQ_09();
void IRQ_10();
void IRQ_11();
void IRQ_12();
void IRQ_13();
void IRQ_14();
void IRQ_15();

#endif
