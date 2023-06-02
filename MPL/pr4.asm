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



hexToAscii : 

	
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
	mov rsi,result
	mov rdx,16
	syscall
	
	ret
	




section .data
	no1 dq 40h
	no2 dq 20h
	
	m1 db "Addition : " ,0xA,0xD
	l1 equ $-m1
	m2 db "Substraction : ",0xA
	l2 equ $-m2
	m3 db "Multiply : " ,0xA,0xD
	l3 equ $-m2
	m4  db "Divide : ",0xA
	l4 equ $-m4
	
	
	msg db 0xA,"Options are 1 -> Add, 2 -> Subtract, 3 -> Multiply, 4 -> Divide",0XA
	len equ $-msg
	
	cnt db 5h
	

section .bss
	result resb 3
	option resb 10
	
	
section .text	
	global _start
	
_start :

	
	
	print msg,len
	input option,10
	mov bl,byte[option]
	
	
	cmp      bl    ,  31h
	jz      add
	cmp      bl    ,  32h
	jz       sub
	cmp      bl    ,  33h
	jz     mul
	cmp      bl    ,  34h
	jz       div
	
	
	add :
	mov rax,10h
	mov rbx,20h
	add rax,rbx
	call hexToAscii
	jmp exit

	sub:
	mov rax,10h
	mov rbx,20h
	sub rax,rbx
	call hexToAscii
	jmp exit

	mul:
	mov rax,05h
	mov rbx,02h
	imul rbx
	push rax
	mov rax,rdx
	call hexToAscii
	pop rax
	call hexToAscii
	jmp exit
	
	div:
	xor rdx,rdx
	mov rax,15h
	mov ebx,05h
	div ebx
	mov rax,rax
	call hexToAscii
	
	jmp exit
	





	
	

	
	

	

	



exit:
mov rax,60
mov rdi,60
syscall
