%macro print  2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
	
%endmacro

%macro input  2
mov rax,00
mov rdi,00
mov rsi,%1
mov rdx,%2
syscall
	
%endmacro




;---------------------------------------------------------------------------------
section .data
	menu:  db 0xA,"1.BCD to HEX 2.HEX to BCD",10
	len equ $-menu
	msg1 db "Enter Number : ",0xA
	len1 equ $-msg1
	msg2 db "Decimal Number : ",0xA
	len2 equ $-msg2
	
	

section .bss
	cnt resb  10
	choice resb 1
	result resb 5
	result1 resb 5
	bcdcode resb 5

;------------------------------------------------------------------------------------
section .text
	global _start:
	
_start:
	input bcdcode,6
	mov rbx,10
	mov rdx,0
	mov rax,0
	mov byte[cnt],5
	mov rsi,bcdcode

	;converting to decimal
unpack:
	mul rbx
	sub byte[rsi],30h
	movsx cx,byte[rsi] ;move with sign extended
	add ax,cx
	inc rsi
	dec byte[cnt]
	jnz unpack
	
	;now we have the decimal value. Convert we have hex val 
	mov byte[cnt],4
	mov rsi,result1
again:
	rol ax,4
	mov bl,al
	and bl,0Fh
	cmp bl,9
	jbe nocorrection2
	add bl,7
nocorrection2:
	add bl,30h
	mov byte[rsi],bl
	inc rsi
	dec byte[cnt]
	jnz again
	print result1,4
	
exit:
mov rax,60
mov rdi,60
syscall


