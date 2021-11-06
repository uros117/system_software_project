.intel_syntax noprefix

.global _start
.extern write
.extern exit

.equ message_lenght, message_end - message_start

.data
message_start:
.asciz "Hello World\n"
message_end:

.text
_start:
	mov rdi, 1
	mov rsi, offset message_start
	mov rdx, message_lenght
	call write

	mov rdi, 13
	call exit
;ld -o exe --dynamic-linker /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 syscall_wrapper.o --library c
.end
