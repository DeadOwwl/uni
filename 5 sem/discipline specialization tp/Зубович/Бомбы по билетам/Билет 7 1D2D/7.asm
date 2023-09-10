.Model tiny
.code
ORG 100H
start:
    Mov ah,1
    Int 21h
	xor ah,ah
	sub al,'0'
	div ten
	add ah,'0'
	mov dl,ah
	mov ah,2
	int 21h
ret
ten db 10
END     start