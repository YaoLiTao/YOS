#ifndef _YOS_PROTECT_H_
#define _YOS_PROTECT_H_ 1

/*----------------------------------------------------------------------------
       DA_  : Descriptor Attribute
       D    : 数据段
       C    : 代码段
       S    : 系统段
       R    : 只读
       RW   : 读写
       A    : 已访问
----------------------------------------------------------------------------*/
#define DA_32			0x4000	//32 位段
#define DA_LIMIT_4K		0x8000	//段界限粒度为 4K 字节

#define DA_DPL0			  0x00	//DPL = 0
#define DA_DPL1			  0x20	//DPL = 1
#define DA_DPL2			  0x40	//DPL = 2
#define DA_DPL3			  0x60	//DPL = 3
/*----------------------------------------------------------------------------
	 存储段描述符类型值说明
----------------------------------------------------------------------------*/
#define DA_DR			0x90	//存在的只读数据段类型值
#define DA_DRW			0x92	//存在的可读写数据段属性值
#define DA_DRWA			0x93	//存在的已访问可读写数据段类型值
#define DA_C			0x98	//存在的只执行代码段属性值
#define DA_CR			0x9A	//存在的可执行可读代码段属性值
#define DA_CCO			0x9C	//存在的只执行一致代码段属性值
#define DA_CCOR			0x9E	//存在的可执行可读一致代码段属性值
/*----------------------------------------------------------------------------
	 系统段描述符类型值说明
----------------------------------------------------------------------------*/
#define DA_LDT			  0x82	//局部描述符表段类型值
#define DA_TaskGate		  0x85	//任务门类型值
#define DA_386TSS		  0x89	//可用 386 任务状态段类型值
#define DA_386CGate		  0x8C	//386 调用门类型值
#define DA_386IGate		  0x8E	//386 中断门类型值
#define DA_386TGate		  0x8F	//386 陷阱门类型值
//----------------------------------------------------------------------------
// 选择子
// SA_  : Selector Attribute
//----------------------------------------------------------------------------
#define SA_RPL0		0	// ┓
#define SA_RPL1		1	// ┣ RPL
#define SA_RPL2		2	// ┃
#define SA_RPL3		3	// ┛

#define SA_TIG		0	// ┓TI
#define SA_TIL		4	// ┛
//----------------------------------------------------------------------------
// 分页机制
//----------------------------------------------------------------------------
#define PG_P		1	// 页存在属性位
#define PG_RWR		0	// R/W 属性位值, 读/执行
#define PG_RWW		2	// R/W 属性位值, 读/写/执行
#define PG_USS		0	// U/S 属性位值, 系统级
#define PG_USU		4	// U/S 属性位值, 用户级
//----------------------------------------------------------------------------

#define BASE_ADDR_OF_GS 0xB8000

#define SELECTOR_ZERO  0
#define SELECTOR_CODE (1 << 3)  // kernel code
#define SELECTOR_DATA (2 << 3)  // kernel data+stack
#define SELECTOR_GS   (3 << 3)  // kernel GS

#define MASTER_8259A 0x21
#define SLAVE_8259A  0xA1


typedef struct
{
	ushort	limit_low;		/* Limit */
	ushort	base_low;		/* Base */
	uchar	base_mid;		/* Base */
	uchar	attr1;			/* P(1) DPL(2) DT(1) TYPE(4) */
	uchar	limit_high_attr2;	/* G(1) D(1) 0(1) AVL(1) LimitHigh(4) */
	uchar	base_high;	/* Base */
}Descriptor;

typedef struct
{
	ushort limit;
	ushort addr_low;
	ushort addr_high;
}GdtPtr;

typedef GdtPtr IdtPtr;

typedef struct
{
	ushort	offset_low;	/* Offset Low */
	ushort	selector;	/* Selector */
	uchar	dcount;		/* 该字段只在调用门描述符中有效。如果在利用
				   调用门调用子程序时引起特权级的转换和堆栈
				   的改变，需要将外层堆栈中的参数复制到内层
				   堆栈。该双字计数字段就是用于说明这种情况
				   发生时，要复制的双字参数的数量。*/
	uchar	attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	ushort	offset_high;	/* Offset High */
}Gate;

//init_descriptor(描述符地址, 段基址, 段限界, 属性)
void init_descriptor(Descriptor *desc, uint base, uint limit, ushort attribute);
//init_gate(门地址, 目标选择子, 偏移, DCount, 属性)
void init_gate(Gate *gate, ushort sel, uint offset, uchar dc, uchar attribute);
//死循环
void suspend();

void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags);

void disp_IRQ(int irq);
#endif