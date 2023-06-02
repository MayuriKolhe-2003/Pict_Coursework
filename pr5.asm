%macro print  2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
	
%endmacro

hexToAscii : 

	
mov byte[cnt],2h
mov rsi,result
	
label4:	rol al,4
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
	
	
	print result , 2
	
	ret
;-------------------------------------------------------------------------------------------



section .data
	
	msg1 db "Count of Positive Numbers : ",0xA
	len1 equ $-msg1
	msg2 db 0xA,"Count of Negative Numbers : ",0xA
	len2 equ $-msg2
	
	array dq 0xAAAA111122223333,0x0000000000000000,0x8000000000000000,0x1000000000020000,0x9000002000000000
	cnt db 5
	
	neg_count db 0
	pos_count db 0
	result db 0


;----------------------------------------------------------------------------------------------

section .text
	global _start
	
_start:
	mov byte[cnt],5
	mov rsi,array
	
	
label1: 	mov rax,[rsi]
	bt rax,63
	jnc pos
	add byte[neg_count],01
	jmp in
pos:	add byte[pos_count],01	
in :	add rsi,8
	dec byte[cnt]
	jnz label1
	
	
	
	
	;----------PRINT POSITIVE COUNT--------
	print msg1,len1
	mov al,byte[pos_count]
	call hexToAscii
	
	;----------PRINT NEGATIVE COUNT--------
	print msg2,len2
	mov al,byte[neg_count]
	call hexToAscii
	
	
	
	


mov rax,60
mov rdi,60
syscall
	
	
