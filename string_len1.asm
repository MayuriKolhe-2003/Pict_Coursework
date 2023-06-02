section .data
	msg1 db "Enter a string : ",0xA
	len1 equ $-msg1
	
	msg2 db "Length of your string : ",0xA
	len2 equ $-msg2
	
	one db 0fh

	
section .bss
	string resb 100
	length resb 100
	
section .text
	global _start

_start : 
	;print msg1
	mov rax,01
	mov rdi,01
	mov rsi,msg1
	mov rdx,len1
	syscall
	
	;input str
	mov rax,00
	mov rdi,00
	mov rsi,string
	mov rdx,100
	syscall
	
	dec rax
	mov r8,length
	mov byte[cnt],2
	mov cx,16

up :
	rol rax,4
	mov bl,al
	and bl,0fh
	cmp bl,09h
	jbe label1
	add bl,07h
label1: 
	add bl,30h
	mov [r8],bl
	inc r8
	dec cx
	jnz up
	
	;print msg2
	mov rax,01
	mov rdi,01
	mov rsi,msg2
	mov rdx,len2
	syscall


	
	;print length of str
	
;mov byte[cnt],2
;mov r8,length

;arrl:
	mov rax,01
	mov rdi,01
	mov rsi,length
	mov rdx,17
	syscall
	
	;inc r8
	;dec byte[cnt]
	;jnz arrl
	
	mov rax,60
	mov rdi,60
	syscall
	
	

