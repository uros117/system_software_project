.intel_syntax noprefix



.global _start

.equ message_lenght, message_end - message_start

.data
message_start:
.asciz "Hello World\n"
message_end:

.text
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, offset message_start
	mov rdx, message_lenght
	syscall

	mov rax, 60
	mov rdi, 13
	syscall

.end
