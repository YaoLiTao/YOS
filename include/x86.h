#ifndef _YOS_X86_H_
#define _YOS_X86_H_

#include <type.h>
#include <protect.h>

/* 
	uint   = 4 byte = 32 bit
   	ushort = 2 byte = 16 bit
   	uchar  = 1 byte = 8  bit
 */


uchar _in_byte(ushort port);					//从端口读一字节
void  _insl(int port, void* addr, int count);	//从端口读入串
void  _out_byte(ushort port, uchar data);		//向端口写入一字节
void  _outsl(int port, void* addr, int count);	//向端口写入串
void  _stosb(void *addr, int data, int count);	//向一个内存地址写数据
void  _lgdt(GdtPtr *p);
void  _lidt(IdtPtr *p);
void  _putc(int pos, int char_and_attr);		//打印一个字符 pos = (x + COLUMNS * y) * 2 char_and_attr = ((a << 8) | (c & 0xff))
void  _sti();
void  _cli();
void  _ud();									//产生一个#UD中断
void  _setCR3(uint* addr);						//把页目录首址存进CR3
void  _setCR0(uint attr);

#endif