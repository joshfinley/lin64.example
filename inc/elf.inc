%ifndef elf_inc
%define elf_in

;---------------------------------------------------------------
; Types
;---------------------------------------------------------------

%define elf64_addr	 qword
%define elf64_half	 word
%define elf64_shalf	 word
%define elf64_off	 qword
%define elf64_sword  dword
%define elf64_word   dword
%define elf64_xword  qword
%define elf64_sxword qword

;---------------------------------------------------------------
; Constants
;---------------------------------------------------------------

%define PT_NULL    0
%define PT_LOAD    1
%define PT_DYNAMIC 2
%define PT_INTERP  3
%define PT_NOTE    4
%define PT_SHLIB   5
%define PT_PHDR    6
%define PT_TLS     7           		; Thread local storage segment 
%define PT_LOOS    0x60000000  		; OS-specific 
%define PT_HIOS    0x6fffffff  		; OS-specific 
%define PT_LOPROC  0x70000000
%define PT_HIPROC  0x7fffffff
%define PT_GNU_EH_FRAME		0x6474e550

%define PT_GNU_STACK 0xc474e550	

; These constants define the different elf file types 
%define ET_NONE   0
%define ET_REL    1
%define ET_EXEC   2
%define ET_DYN    3
%define ET_CORE   4
%define ET_LOPROC 0xff00
%define ET_HIPROC 0xffff


; This is the info that is needed to parse the dynamic section of the file 
%define DT_NULL		0
%define DT_NEEDED	1
%define DT_PLTRELSZ	2
%define DT_PLTGOT	3
%define DT_HASH		4
%define DT_STRTAB	5
%define DT_SYMTAB	6
%define DT_RELA		7
%define DT_RELASZ	8
%define DT_RELAENT	9
%define DT_STRSZ	10
%define DT_SYMENT	11
%define DT_INIT		12
%define DT_FINI		13
%define DT_SONAME	14
%define DT_RPATH 	15
%define DT_SYMBOLIC	16
%define DT_REL	        17
%define DT_RELSZ	18
%define DT_RELENT	19
%define DT_PLTREL	20
%define DT_DEBUG	21
%define DT_TEXTREL	22
%define DT_JMPREL	23
%define DT_ENCODING	32
%define OLD_DT_LOOS	0x60000000
%define DT_LOOS		0x6000000d
%define DT_HIOS		0x6ffff000
%define DT_VALRNGLO	0x6ffffd00
%define DT_VALRNGHI	0x6ffffdff
%define DT_ADDRRNGLO	0x6ffffe00
%define DT_ADDRRNGHI	0x6ffffeff
%define DT_VERSYM	0x6ffffff0
%define DT_RELACOUNT	0x6ffffff9
%define DT_RELCOUNT	0x6ffffffa
%define DT_FLAGS_1	0x6ffffffb
%define DT_VERDEF	0x6ffffffc
%define	DT_VERDEFNUM	0x6ffffffd
%define DT_VERNEED	0x6ffffffe
%define	DT_VERNEEDNUM	0x6fffffff
%define OLD_DT_HIOS     0x6fffffff
%define DT_LOPROC	0x70000000
%define DT_HIPROC	0x7fffffff

; This info is needed when parsing the symbol table 
%define STB_LOCAL  0
%define STB_GLOBAL 1
%define STB_WEAK   2

%define STT_NOTYPE  0
%define STT_OBJECT  1
%define STT_FUNC    2
%define STT_SECTION 3
%define STT_FILE    4
%define STT_COMMON  5
%define STT_TLS     6

; These constants define the various ELF target machines 
%define EM_NONE		0
%define EM_MIPS		8				; MIPS R3000 (officially, big-endian only) 
%define EM_MIPS_RS3_LE	10			; MIPS R3000 little-endian 
%define EM_MIPS_RS4_BE	10			; MIPS R4000 big-endian 
%define EM_ARM		40				; ARM 32 bit 
%define EM_X86_64	62				; AMD x86-64 
%define EM_AARCH64	183				; ARM 64 bit 
%define EM_BPF		247				; Linux BPF - in-kernel virtual machine 

%define EM_ALPHA	0x9026

; Bogus old m32r magic number, used by old tools. 
%define EM_CYGNUS_M32R	0x9041

; This is the old interim value for S/390 architecture 
%define EM_S390_OLD	0xA390

; Also Panasonic/MEI MN10300, AM33 
%define EM_CYGNUS_MN10300 0xbeef

;---------------------------------------------------------------
; Structures
;---------------------------------------------------------------

; https://github.com/vxunderground/MalwareSourceCode/blob/8ce86aa641299d8cfa13ce801bcb6a6b292d6f9b/VXUG/Linux.Kropotkine.asm
;

struc STAT
    .st_dev         resq 1
    .st_ino         resq 1
    .st_nlink       resq 1
    .st_mode        resd 1
    .st_uid         resd 1
    .st_gid         resd 1
    .pad0           resb 4
    .st_rdev        resq 1
    .st_size        resq 1
    .st_blksize     resq 1
    .st_blocks      resq 1
    .st_atime       resq 1
    .st_atime_nsec  resq 1
    .st_mtime       resq 1
    .st_mtime_nsec  resq 1
    .st_ctime       resq 1
    .st_ctime_nsec  resq 1
endstruc

struc e_hdr
	.magic		resd 1 ; 0x7F followed by ELF(45 4c 46) in ASCII; these four bytes constitute the magic number. 
	.class		resb 1 ; This byte is set to either 1 or 2 to signify 32- or 64-bit format, respectively. 
	.data		resb 1 ; This byte is set to either 1 or 2 to signify little or big endianness, respectively. This affects interpretation of multi-byte fields starting with offset 0x10. 
	.elf_version resb 1 ; Set to 1 for the original and current version of ELF. 
	.os 		resb 1 ; Identifies the target operating system ABI. 
	.abi_version resb 1
	.padding	resb 7 ; currently unused, should be filled with zeros. <--------- that will be the place where we will put out signature
	.type		resb 2 ; Identifies object file type. 
	.machine	resb 2 ; Specifies target instruction set architecture.
	.e_version	resb 4 ; Set to 1 for the original version of ELF. 
	.entry		resq 1 ; this is the entry point
	.phoff		resq 1 ; Points to the start of the program header table.
	.shoff		resq 1 ; Points to the start of the section header table. 
	.flags		resb 4 ; Interpretation of this field depends on the target architecture. 
	.ehsize		resb 2 ; Contains the size of this header, normally 64 Bytes for 64-bit and 52 Bytes for 32-bit format. 
	.phentsize	resb 2 ; Contains the size of a program header table entry. 
	.phnum		resb 2 ; Contains the number of entries in the program header table. 
	.shentsize	resb 2 ; Contains the size of a section header table entry. 
	.shnum		resb 2 ; Contains the number of entries in the section header table. 
	.shstrndx	resb 2 ; Contains index of the section header table entry that contains the section names. 
	.end		resb 1
endstruc

struc e_phdr
	.type	resb 4 ; Identifies the type of the segment. (The number which interest us are: 0 = PT_NULL | 1 = PT_LOAD | 2 = PT_DYNAMIC | 4 = PT_NOTE)
	.flags	resd 1 ; Segment-dependent flags (position for 64-bit structure). 
	.offset resq 1 ; Offset of the segment in the file image. 
	.vaddr	resq 1 ; Virtual address of the segment in memory. 
	.paddr	resq 1 ; On systems where physical address is relevant, reserved for segments physical address.
	.filesz resq 1 ; Size in bytes of the segment in the file image.
	.memsz 	resq 1 ; Size in bytes of the segment in memory.
	.align	resq 1 ; 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr equating p_offset modulus p_align.
	.end	resb 1
endstruc

struc e_shdr
	.name	resb 4 ; An offset to a string in the .shstrtab section that represents the name of this section. 
	.type	resb 4 ; Identifies the type of this header.
	.flags	resq 1 ; Identifies the attributes of the section. 
	.addr   resq 1 ; Virtual address of the section in memory, for sections that are loaded. 
	.offset resq 1 ; Offset of the section in the file image. 
	.size   resq 1 ; Size in bytes of the section in the file image.
	.link   resb 4
	.info   resb 4
	.addralign resq 1 ; Contains the required alignment of the section. 
	.entsize resq 1 ; Contains the size, in bytes, of each entry, for sections that contain fixed-size entries.
	.end	resb 1
endstruc

%endif ; !elf_inc
