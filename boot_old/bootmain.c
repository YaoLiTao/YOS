#include "const.h"
#include "type.h"
#include "elf.h"
#include "x86.h"
#include "menlayout.h"


#define SECTSIZE 512

void readseg(uchar* pa, uint count, uint offset);

void bootmain(){
	elfhdr *elf;
	proghdr *ph, *eph;
	void (*entry)(void);
	uchar* pa;
	//指针的类型决定了每次+1所地址增加的单位, 指针本身是32位

	elf = (elfhdr*) BaseOfKernelFile;

	readseg((uchar*)elf, 4096, 0);

	if(elf->magic != ELF_MAGIC)
    return;

	ph = (struct proghdr*)((uchar*)elf + elf->phoff);
  	eph = ph + elf->phnum;
  	for(; ph < eph; ph++){
    	pa = (uchar*)ph->paddr;
    	readseg(pa, ph->filesz, ph->off);
    	if(ph->memsz > ph->filesz)
      		_stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
  	}

  	entry = (void(*)(void))(elf->entry);
  	entry();
}

void waitdisk()
{
  	while((in_byte(0x1F7) & 0xC0) != 0x40);
}

//每次读一个扇区到指定的内存地址
void readsect(void *dst, uint lba)
{
	// 	C (Cylinder)表示当前柱面 
	//  H (Head)表示当前磁头
	// 	S (Sector)表示当前扇区
	//	Cs表示起始柱面号, Hs表示起始磁头号, Ss表示起始扇区号
	//	PS表示每磁道有多少个扇区, PH表示每柱面有多少个磁道
	// 	lba寻址模式, LBA=（C-Cs）*PH*PS+（H-Hs）*PS+（S-Ss） 
	//  起始扇区一般为1, lba为偏移量
	//	C/H/S=0/0/1, LBA=0
	waitdisk();
	out_byte(0x1F2, 1);   			// 	count = 1 要读的扇区数
	out_byte(0x1F3, lba); 			//	LBA参数的0~7位
	out_byte(0x1F4, lba >> 8);		//	LBA参数的8~15位
	out_byte(0x1F5, lba >> 16);		//	LBA参数的16~23位
	out_byte(0x1F6, (lba >> 24) | 0xE0);	//7~5位,111,第4位0表示主盘,1表示从盘,3~0位,LBA参数的24~27位
	out_byte(0x1F7, 0x20);  // cmd 0x20 - read sectors

	waitdisk();
	_insl(0x1F0, dst, SECTSIZE/4);
}

void readseg(uchar* pa, uint count, uint offset){
	uchar* epa;
	epa = pa + count;
	pa -= offset % SECTSIZE;
	offset = (offset / SECTSIZE) + 1;
	for(; pa < epa; pa += SECTSIZE, offset++)
	  	readsect(pa, offset);
}