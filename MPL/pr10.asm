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
;----------------------------------------------------------------------------------
section .data
	num db 00h
	msg db "Factorial is : "
	msglen equ $-msg
	msg1 db "Program to find Factorial of a number",0Ah
		 db "Enter the number : ",
	msg1len equ $-msg1
	
	zerofact db " 00000001 "
	zerofactlen equ $-zerofact
;--------------------------------------------------------------------------------------
section .bss
	dispnum resb 16
	result resb 4
	temp resb 3
	
;-------------------------------------------------------------------------------------
section .text
global _start
_start:
	print msg1, msg1len
	input temp, 3		;accept number from user
	call convert		;convert number from ascii to hex
	mov [num], dl
	
	print msg, msglen
	
	xor rdx, rdx
	xor rax, rax

	mov al, [num]		;store number in accumulator
	cmp al, 01h              	;number is zeroorone 			
	jbe endfact

	xor rbx, rbx
	mov bl, 01h
	call factr			;call factorial procedure
	call display

	call Exit
endfact:
	print zerofact, zerofactlen

Exit:				;exit system call   
    mov rax, 60
    mov rdx, 00
    syscall

;----------------------------------------------------------------------
factr:				;recursive procedure
    cmp rax, 01h
    je retcon1
    push rax			
    dec rax
    
    call factr

    retcon:
        pop rbx
        mul ebx
        jmp endpr

    retcon1:			;if rax=1 return
        pop rbx
        jmp retcon		
    endpr:
        ret
;--------------------------------------------------------------------------
display:			; procedure to convert hex to ascii
        mov rsi,dispnum+15
        xor rcx,rcx
        mov cl,16

    cont:
        xor rdx,rdx
        xor rbx,rbx
        mov bl,10h
        div ebx
        cmp dl,09h
        jbe skip
        add dl,07h
    skip:
        add dl,30h
        mov [rsi],dl
        dec rsi
        loop cont

        print dispnum,16

        ret
;----------------------------------------------------------------------------
convert:			;procedure to convert ascii to hex
        mov rsi,temp
        mov cl,02h
        xor rax,rax
        xor rdx,rdx
    contc:
        rol dl,04h
        mov al,[rsi]
        cmp al,39h
        jbe skipc
        sub al,07h
    skipc:
        sub al,30h
        add dl,al
        inc rsi
        dec cl
        jnz contc

    ret
