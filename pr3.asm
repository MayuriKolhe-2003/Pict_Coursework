section .data
	msg1 db "Enter 5 numbers : ",0xA
	len1 equ $-msg1
	msg2 db "Largest Number : ",0xA
	len2 equ $-msg2
	
	cnt db 5
	array  dq 0000000000000018h,0000000000000012h,0000000000000014h,0000000000000016h,0000000000000020h
	
section .bss
	result resb 100
	
section .text	
	global _start
	
_start : 
	;---------LARGEST NUMBER LOGIC
	
mov byte[cnt],5
mov rsi,array
mov rax,0000

label2 :
	mov rbx,qword[rsi]
	cmp rbx,rax
	jb label3
	mov rax,rbx
label3:	add rsi,8
	dec byte[cnt]
	jnz label2
	

	;--------HEX TO ASCII
mov byte[cnt],5	
	
hTa:	

mov byte[cnt],10h
mov rsi,result
	
label4:	rol rax,4
	mov bl,al
	and bl,0fh
	cmp bl,09h
	jbe label5
	add bl,07h
	

label5:	add bl,30h
	mov [rsi],bl
	inc rsi
	dec byte[cnt]
	jnz label4
	

	
	
	mov rax,01
	mov rdi,01
	mov rsi,msg2
	mov rdx,len2
	syscall
	
	mov rax,01
	mov rdi,01
	mov rsi,result
	mov rdx,16
	syscall

	
	
	
	
	
mov rax,60
mov rsi,60
syscall
	
