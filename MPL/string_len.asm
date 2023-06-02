section .data
	msg1 db "Enter a string : ",0xA
	len1 equ $-msg1
	
	msg2 db "Length of your string : ",0xA
	len2 equ $-msg2
	
	ab db 50
	
section .bss
	string resb 100
	lens resb 100
	
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
	
	dec al
	cmp al,09h
	jbe label1
	add al,07h
label1: 
	add al,30h
	mov byte[lens],al
	
	;print msg2
	mov rax,01
	mov rdi,01
	mov rsi,msg2
	mov rdx,len2
	syscall
	
	;print length of str
	mov rax,01
	mov rdi,01
	mov rsi,lens
	mov rdx,10
	syscall
	
	mov rax,60
	mov rdi,60
	syscall
	
	
	
	
