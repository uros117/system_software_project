.intel_syntax noprefix

.global main

.extern sum
.extern printf

.data
labela_poruke:
.asciz "Sum of 1 and 3 is %d\n"	
# asciz ima na kraju \0 karaker kao u c-u
# u asm-u jedan .long zauzima 4B a u c-u jedan int za uzima 4B
.text
main:
	push rbp		
	# r su standardni nastavci za ovu arhitekturu
	mov rbp, rsp
	
	mov edi, 1
	mov esi, 3
	call sum		
	# sum vraca vrednost kroz akumulator (eax)
	
	mov rdi, offset labela_poruke	
	# offset se stavlja jer ne znamo gde
	# pocinje data sekcija i linker razresava
	mov esi, eax
	call printf
	
	leave
	# leave radi isto sto i sledece 2 instrukcije
	# mov rsp, rbp
	# pop rbp
	
	ret

.end
