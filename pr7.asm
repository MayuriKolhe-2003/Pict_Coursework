%macro print  2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
	
%endmacro

;-----------------------------------------------------------------------
section .data
	rmodemsg db 10,'Processor is in Real Mode'
    rmsg_len:equ $-rmodemsg

    pmodemsg db 10,'Processor is in Protected Mode'
    pmsg_len:equ $-pmodemsg

    gdtmsg db 10,'GDT Contents are::'
    gmsg_len:equ $-gdtmsg

    ldtmsg db 10,'LDT Contents are::'
    lmsg_len:equ $-ldtmsg

    idtmsg db 10,'IDT Contents are::'
    imsg_len:equ $-idtmsg

    trmsg db 10,'Task Register Contents are::'
    tmsg_len: equ $-trmsg

    mswmsg db 10,'Machine Status Word::'
    mmsg_len:equ $-mswmsg

    colmsg db ':'

    nwline db 10

;-------------------------------------------------------------------------
section .bss
    gdt resd 1
        resw 1
    ldt resw 1
    idt resd 1
        resw 1
    tr  resw 1

    cr0_data resd 1

    ascii_num resb 04

;-------------------------------------------------------------------------
section .text
global _start
_start:
	smsw eax		;storing msw
	mov [cr0_data],rax
	bt rax,1	;Checking PE bit, if 1=Protected Mode, else Real Mode
	jc prmode
	print rmodemsg,rmsg_len	;msg for real mode
prmode:	print pmodemsg,pmsg_len


next:	
	sgdt [gdt]
	sldt [ldt]
	sidt [idt]
	str [tr]
	
;-------------Displaying GDT content------------------
	print gdtmsg,gmsg_len	;global DT
	
	mov bx,[gdt+4]
	call print_num
	mov bx,[gdt+2]
	call print_num
	
	print colmsg,1
	mov bx,[gdt]
	call print_num
	
;-------------Displaying LDT content------------------
	print ldtmsg,lmsg_len	;local DT
	mov bx,[gdt]
	call print_num	
	
;-------------Displaying IDT content------------------
	print idtmsg,imsg_len	;interrupt DT

		
	mov bx,[idt+4]
	call print_num
	mov bx,[idt+2]
	call print_num
	
	print colmsg,1
	mov bx,[idt]
	call print_num	

;-------------Displaying TR content------------------
	print trmsg,tmsg_len	
	mov bx,[tr]
	call print_num	
	
;-------------Displaying MSW content------------------
	print mswmsg,mmsg_len	
	
	mov bx,[cr0_data+2] 
	call print_num

	mov bx,[cr0_data]  
	call print_num

	print nwline,1


exit: 
    mov rax, 60
    mov rdx, 00 
    syscall
    
    
    
;---------------------------- HEX TO ASCII  ---------------------------------------------
print_num:
    mov rsi, ascii_num  

    mov rcx,04         

    up1:
        rol bx,4        
        mov dl,bl       
        and dl,0fh      
        add dl,30h     
        cmp dl,39h     
        jbe skip1       
        add dl,07h      
    skip1:
        mov [rsi],dl    
        inc rsi         
        loop up1        
                        
        print ascii_num, 4   
        
    ret   
