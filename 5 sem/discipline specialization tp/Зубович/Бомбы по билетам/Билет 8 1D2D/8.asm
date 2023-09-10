.model small
.stack 100h
.data
 
.code
start:
	mov ax,@data 
	mov ds,ax
 
; получить адрес своего PSP
  mov  ah,62h ;находим адрес PSP и записываем его в bx
  int  21h
 
; получить адрес Environment
  mov  es,bx ;адрес PSP записываем в es
  mov  ax,es:[002Ch] ; записываем в ax адрес сегмента PSP со смещением 002ch
  mov  es,ax
  mov  ds,ax
 
; найти имя
  cld    ;обнуляет признак направления
  xor  ax,ax ;обуляем ax
  mov  di,ax
  mov  cx,7FFFh
metka1:
  repne	scasb    ;повторяем 
  cmp  al,[di] ;сравниваем al и di
  jnz  metka1
  add  di,6
 
; вывести имя
metka2:
	
  cmp  byte ptr [di],0
  jz   metka3
  mov  dl,[di]
  inc  di 
  mov  ah,2 ;вывод
  int  21h
  jmp  metka2
  
metka3:
  mov  ax,4C00h
  int  21h
 
end start
