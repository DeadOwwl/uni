.model small
.data
    fname db '2.exe', 0
    MSGOK       db 'deleted$'
    MSG1        db 'not found$'    
    MSG2        db 'not right dir$'
    MSG3        db 'no roots$'
; -----------------------
.code
start :
    MOV AX, @DATA
    MOV DS, AX
; --------------------------------
    MOV AH,41h 
    lea dx, fname 
    INT 21H
    JC  ERROR1 
    MOV AH,09h
    MOV DX,OFFSET MSGOK
    INT 21h
FIN:
    MOV AX,4C00h
    INT  21h               

;---------------------------------
                               
ERROR1:   
    MOV AH,02h
    JE  NOTFOUND
    MOV AX,03h
    JE  WRONGDIR
    CMP  AX,05h
    JE  NOACCESS
    JMP FIN 
NOTFOUND:   
    MOV DX,OFFSET MSG1
    JMP WRITE
WRONGDIR:   
    MOV DX,OFFSET MSG2
    JMP WRITE
NOACCESS:   
    MOV DX,OFFSET MSG3
WRITE:          
    MOV AH,09h
    INT 21h
    JMP FIN
end start
