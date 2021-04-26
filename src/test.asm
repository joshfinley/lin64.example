bits 64

%include "../inc/elf.inc"

global _start
section .text

_start:
	mov al, 0x3c
	xor rdi, rdi
	syscall


