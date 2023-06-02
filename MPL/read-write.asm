section .data
	msg1 db "Enter your name : ",0xA
	len1 equ $-msg1
	msg2 db "Your name is : "
	len2 equ $-msg2
	msg3 db "Enter the number : "
	len3 equ $-msg3
	
	cnt db 5h
	
section .bss
	name resb 10
	no resb 5

section .text
	global _start
	
	_start:

	;print msg1
	mov rax,01
	mov rdi,01
	mov rsi,msg1
	mov rdx,len1
	syscall
	
	;input name
	mov rax,00
	mov rdi,00
	mov rsi,name
	mov rdx,20
	syscall
	
	;print msg2
	mov rax,01
	mov rdi,01
	mov rsi,msg2
	mov rdx,len2
	syscall
	
	;output name
	mov rax,01
	mov rdi,01
	mov rsi,name
	mov rdx,20
	syscall
	
	
	
	;print msg3
	mov rax,1
	mov rdi,01
	mov rsi,msg3
	mov rdx,len3
	syscall
	
	;input no
	mov rax,00
	mov rdi,00
	mov rsi,no
	mov rdx,5
	syscall
	
	;loop to print no cnt times
	label1:
		mov rax,01
		mov rdi,01
		mov rsi,no
		mov rdx,5
		syscall
		
		dec byte[cnt]
		jnz label1
		

	
	
	mov rax,60
	mov rdi,60
	syscall






