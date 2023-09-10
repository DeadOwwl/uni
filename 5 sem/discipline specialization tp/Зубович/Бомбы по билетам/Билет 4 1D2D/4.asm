.model small
.data
	s db "\0-00",10,13,"\a-07",10,13,"\b-08",10,13,"\t-09",10,13,"\n-0A",10,13,"\v-0B",10,13,"\f-0C",10,13,"\r-0D",10,13,"\e-1B$" 
.code
start:
  mov ax, @data
  mov ds, ax
 
  mov ah, 09h
  mov dx, offset s
  int 21h
  
  mov ax, 4c00h
  int 21h
end start
