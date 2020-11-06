#ifndef _YOS_ELF_
#define _YOS_ELF_

#include "type.h"

#define ELF_MAGIC 0x464C457FU  // "\x7FELF" in little endian

// File header
typedef struct{
  uint magic;  // must equal ELF_MAGIC
  uchar elf[12];
  ushort type;
  ushort machine;
  uint version;
  uint entry;
  uint phoff;
  uint shoff;
  uint flags;
  ushort ehsize;
  ushort phentsize;
  ushort phnum;
  ushort shentsize;         
  ushort shnum;
  ushort shstrndx;
}elfhdr;

// Program section header
typedef struct{
  uint type;
  uint off;
  uint vaddr;
  uint paddr;
  uint filesz;
  uint memsz;
  uint flags;
  uint align;
}proghdr;

// Values for Proghdr type
#define ELF_PROG_LOAD           1

// Flag bits for Proghdr flags
#define ELF_PROG_FLAG_EXEC      1
#define ELF_PROG_FLAG_WRITE     2
#define ELF_PROG_FLAG_READ      4


#endif