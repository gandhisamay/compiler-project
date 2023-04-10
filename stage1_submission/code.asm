%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

sys_exit equ 60
	default rel
	global _start

section .text
_start:
mov rax, 1
mov rax, sys_exit

syscall
