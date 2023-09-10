.model small
.code
start:
  mov al, 1
  mov bl, 2;colour
  mov dh, 0;row
  mov dl, 0;column
printing:
  mov ah, 02h
  int 10h
  mov dl, 0
new_item:
  mov ah, 02h
  int 10h
  mov ah, 09h
  mov cx, 1
  int 10h
  inc al
  
  inc dl
  cmp dl, 16
  jne new_item
  
  inc dh
  cmp dh, 16
  jne printing

  mov ax, 4c00h
  int 21h
end start