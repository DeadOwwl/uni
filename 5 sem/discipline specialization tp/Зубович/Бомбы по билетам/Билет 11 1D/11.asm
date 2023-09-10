.model small
.data
  path db "1.txt",0
	mes  db 13,10,"R/W$"
	mes1 db 13,10,"RO$"
	mes2 db 13,10,"Hidden$"
	mes3 db 13,10,"System$"
	mes4 db 13,10,"Label$"
	mes5 db 13,10,"Dir$"
	mes6 db 13,10,"Archive$"
.code
start:
  mov ax,@data
  mov ds,ax
  mov ah, 43h
  mov al,0
  mov dx, offset path
  int 21h
  
m : mov ax,cx
    cmp ax,000000001b
    jnz m1 
    mov ah, 09h
    mov dx,offset mes
    int 21h
	
m1: mov ax,cx
    and ax,000000010b
    jz m2 
    mov ah, 09h
    mov dx,offset mes1
    int 21h
    

m2: mov ax,cx
    and ax,000000100b
    jz m3 
    mov ah, 09h
    mov dx,offset mes2
    int 21h
    
m3: mov ax,cx
    and ax,0004h
    jz m4 
    mov ah, 09h
    mov dx,offset mes3
    int 21h
    
m4: mov ax,cx
    and ax,0008h
    jz m5 
    mov ah, 09h
    mov dx,offset mes4
    int 21h
    
m5: mov ax,cx
    and ax,0010h
    jz m6 
    mov ah, 09h
    mov dx,offset mes5
    int 21h
    
m6: mov ax,cx
    and ax,0020h
    jz mx 
    mov ah, 09h
    mov dx,offset mes6
    int 21h
	
mx: mov ax, 4c00h
    int 21h
end start