use64
format ELF64

include '../inc/lin.inc'

section '.text' executable

public _start
_start:
	mov al, 0x3c
	xor rdi, rdi
	syscall
