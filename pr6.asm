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
	msg1 db "Enter BCD Number : ",0xA
	len1 equ $-msg1
	msg2 db "Enter HEX Number : ",0xA
	len2 equ $-msg2
	blank db "",0xA
	blen equ $-blank
	
	

section .bss
	cnt resb  10
	hexcode resb 5
	bcdcode resb 5
	choice resb 2
	result resb 5
	result1 resb 5

;------------------------------------------------------------------------------------
section .text
	global _start:
	
_start:

	print menu,len
	input choice,2
	cmp byte[choice],31h
	je HTB
	cmp byte[choice],32h
	je BTH
	cmp byte[choice],33h
	je exit
	jmp _start   ;jump to start if invalid choice is entered
	

HTB:
	print msg1,len1
	input hexcode,4

xor rax,rax
	mov rsi,hexcode
	mov byte[cnt],04h
ascii:                                    ;ascii_hex to actual hex
	mov dl,byte[rsi]
	cmp dl,39h
	jbe l1
	sub dl,07h
l1:
	sub dl,30h
	rol ax,04h
	add al,dl
	inc rsi
	dec byte[cnt]
	jnz ascii
	 	
	;-------HEX TO BCD------------
	xor rdx,rdx
	mov ebx,0xA
	mov byte[cnt],04h
conv:                                                
	div ebx      
	push rdx
	xor rdx,rdx
	dec byte[cnt]
	jnz conv
	 
	mov byte[cnt],04h
	xor rbx,rbx
pop1:
	pop rbx
	add rbx,30h                            ;rbx contains only single digit 0-9
	mov [result],rbx   	       ;hence adding only 30
	print result,1
	dec byte[cnt]
	jnz pop1
	
	print blank,blen
	jmp _start
	
	
	
	;-------BCD TO HEX------------
BTH:	
	print msg2,len2
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
	jbe skip
	add bl,7
skip:
	add bl,30h
	mov byte[rsi],bl
	inc rsi
	dec byte[cnt]
	jnz again
	print result1,4
	
	print blank,blen
	jmp _start
	
	
	
	
exit:
mov rax,60
mov rdi,60
syscall
	
