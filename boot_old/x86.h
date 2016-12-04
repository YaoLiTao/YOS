#ifndef _YOS_X86_H_
#define _YOS_X86_H_

/* 
	uint   = 4 byte = 32 bit
   	ushort = 2 byte = 16 bit
   	uchar  = 1 byte = 8  bit
 */

uchar in_byte(ushort port);					//从端口读一字节
void _insl(int port, void* addr, int count);	//从端口读入串


void out_byte(ushort port, uchar data);		//向端口写入一字节
void _outsl(int port, void* addr, int count);//向端口写入串


void _stosb(void *addr, int data, int count);


#endif