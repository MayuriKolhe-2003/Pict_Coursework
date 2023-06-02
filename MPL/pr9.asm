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



;-----------------------------------------------------------------------
section .data
	global msg6,len6,scount,ncount,chacount,new,new_len

	fname: db 'pr9_text.txt',0

	msg: db "File opened successfully",0x0A
	len: equ $-msg

	msg1: db "File closed successfully",0x0A
	len1: equ $-msg1

	msg2: db "Error in opening file",0x0A
	len2: equ $-msg2

	msg3: db "Spaces:",0x0A
	len3: equ $-msg3

	msg4: db "NewLines:",0x0A
	len4: equ $-msg4

	msg5: db "Enter character",0x0A
	len5: equ $-msg5

	msg6: db "No of occurances:",0x0A
	len6: equ $-msg6

	new: db "",0x0A
	new_len: equ $-new

	scount: db 0
	ncount: db 0
	ccount: db 0
	chacount: db 0

;-----------------------------------------------------------------------
section .bss
	global cnt,cnt2,cnt3,buffer
	
	fd: resb 17
	buffer: resb 200
	buf_len: resb 17
	cnt: resb 2
	cnt2: resb 2
	cnt3: resb 2
	cha: resb 2

;-----------------------------------------------------------------------
section .text
global _start
_start:
	extern spaces,enters,occ
	
	mov rax,2
	mov rdi,fname
	mov rsi,2
	mov rdx,0777
	syscall
	
	mov qword[fd],rax
	bt rax,63
	jc next
	print msg,len
	jmp next2
	next:
	print msg2,len2
	
	next2:
	mov rax,0
	mov rdi,[fd]
	mov rsi,buffer
	mov rdx,200
	syscall
	
	mov qword[buf_len],rax
	mov qword[cnt],rax
	mov qword[cnt2],rax
	mov qword[cnt3],rax
	
	print msg3,len3
	call spaces
	
	print msg4,len4
	call enters
	
	print msg5,len5
	input cha,2
	print msg6,len6
	mov bl, byte[cha]
	call occ
	jmp exit
	
	
	
	
	




exit:
mov rax,60
mov rdi,0
syscall
