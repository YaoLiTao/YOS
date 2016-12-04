#ifndef _YOS_MENLAYOUT_H_
#define _YOS_MENLAYOUT_H_

#define KernelEntryPointPhyAddr	0x30400
//1、必须与 MAKEFILE 中参数 -Ttext 的值相等!!
//2、这是个地址而非仅仅是个偏移，如果 -Ttext 的值为 0x400400，则它的值也应该是 0x400400。

#define PageDirBase		0x200000	//页目录开始地址:		2M
#define PageTblBase		0x201000	//页表开始地址:			2M + 4K


#endif