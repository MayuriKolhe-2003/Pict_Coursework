section .data
	msg1 db "Enter 5 number : ",0xA
	len1 equ $-msg1
	
	msg2 db "Entered numbers are : ",0xA
	len2 equ $-msg2
	
	cnt db 5h

section .bss
	array resb 100	

section .text
	global _start
	
_start :

	mov rax,01
	mov rdi,01
	mov rsi,msg1
	mov rdx,len1
	syscall
	
mov byte[cnt],5
mov r8,array

label1 :
	mov rax,00
	mov rdi,00
	mov rsi,r8
	mov rdx,17
	syscall
	
	add r8,17
	dec byte[cnt]
	jnz label1

	mov rax,01
	mov rdi,01
	mov rsi,msg2
	mov rdx,len2
	syscall
	
mov byte[cnt],5	
mov r8,array
label2 :
	mov rax,01
	mov rdi,01
	mov rsi,r8
	mov rdx,17
	syscall
	
	add r8,17
	dec byte[cnt]
	jnz label2
	
	mov rax,60
	mov rdi,60
	syscall
	

	
	
