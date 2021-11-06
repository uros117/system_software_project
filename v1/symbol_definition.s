; reci sa tackom ispred su direktive
; 3 osnovne sekcije:
; .text 
; 	sluzi na radbe
; .data 
; 	nalaze se staticke promenljive koje su inicijalizovane
; 	staticke promenljive su globalne promenljive ili staticke
; 	lokalne promenljive
; .bss
; 	ne inicijalizovane staticke promenljive
; .global s
; .equ
; .long
; .extern c
;	ja ne znam koja je ovo promenljiva ali linker ce je naci
; .section .ime_sekcije
;	ako hocemo da definisemo sekciju koja nije jedna od 3
; .end
;	uvek se nalazi na kraju sekcije

.global symbol1
.global symbol2
.global symbol3
.global symbol4

.data
symbol1:
symbol2:
symbol3:
symbol4:
.long 9
.long 8
.long 7
.long 6
.long 5
.long 4
.long 3
.long 2
.long 1
.long 0

.end
