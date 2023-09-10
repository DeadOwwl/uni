.model small
.stack 100h
.data
    p1 db 'abcd'
    len dw 4
    p_e db 'passwords are equal$'       
    n_e db 'passwords are not equal$'   
    buf db 82 dup (?)
.code
start:  
    mov ax,@data
    mov ds,ax
    mov ah,3fh     
    mov bx, 0     
    mov cx,82       
    lea dx,buf     
    int 21h

    mov bx, len 
    sub ax, 2        
    sub ax,bx
    cmp ax, 0      
    je @e           
    mov ah, 09h
    lea dx, n_e
    int 21h
    jmp exit        
@e: 
    cld 
	MOV  AX,  @data
	MOV  DS,  AX
	MOV  ES,  AX	
    lea si, p1
    lea di, buf
    mov cx, len
    repe cmpsb
    jne @not_equal

    mov ah, 09h
    lea dx, p_e
    int 21h
    JMP exit

@not_equal:
    mov ah, 09h
    lea dx, n_e
    int 21h 

exit:   
    mov ax,4c00h
    int 21h
end start