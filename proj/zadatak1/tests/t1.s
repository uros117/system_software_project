#push 1
#.word sym, 5
.extern e3
.extern e1, e2
.global sym1, sym2, sym3


.section data
.equ symb4, 5
labela1:
sym1:
halt # komentar
call 0xFF00
push r0
not r1
.end

.section text
ldr r1, r2
.end
