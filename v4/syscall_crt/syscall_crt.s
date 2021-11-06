.intel_syntax noprefix

.global main
.extern write
.extern exit

.equ message_length, message_end - message_start

.data
message_start:
.asciz "hello world\n"
message_end:

.text
main:
	mov rdi, 1
	mov rsi, offset message_start
	mov rdx, message_length
	call write

	mov rdi, 13
	call exit
	; moraju se ukljuciti 3 biblioteke da bi se kompajlirao
	; i znao da treba da se pozove main
.end
