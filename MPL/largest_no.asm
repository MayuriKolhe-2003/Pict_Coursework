section .data
	msg1 db "Enter 5 numbers : ",0xA
	len1 equ $-msg1
	msg2 db "Largest Number : ",0xA
	len2 equ $-msg2
	
	cnt db 5
	;array times 5 db 1,2,3,4,5
	
	
	
section .bss
	
	 max resb 20
	
section .text	
	global _start
	
_start : 
	
	mov rax,01
	mov rsi,01
	mov rdi,msg1
	mov rdx,len1
	syscall

	
	
mov rax,60
mov rsi,60
syscall
