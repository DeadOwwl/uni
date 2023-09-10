.686

PUBLIC InputElement
PUBLIC InputElementCd
PUBLIC @InputElementFC@12

.model flat
.data
.code

;======================================================
InputElement proc stdcall, Array:dword, N:dword, k:dword

	mov ebx, Array
	mov ecx, N
	mov edx, k
	mov eax, [ebx]
	cmp eax, [ebx+4]
	jg Ubyvanije

Vozrastanije:
	xor eax, eax

	cmp edx, [ebx]
	jl V0

for_Vozr:
	add ebx, 4
	cmp ecx,1
	je V2
	cmp [ebx],edx
	jge V1
	dec ecx
	jmp for_Vozr

V0: inc ecx
V1: cmp ecx, 0
	je KONEC
	mov eax, [ebx]
	mov [ebx], edx
	add ebx, 4
	mov edx, eax
	dec ecx
	jmp V1

V2: mov [ebx], edx
	jmp KONEC

Ubyvanije:
	xor eax, eax

	cmp edx, [ebx]
	jg U0

for_Ubyv:
	add ebx, 4
	cmp ecx,1
	je U2
	cmp [ebx],edx
	jle U1
	dec ecx
	jmp for_Ubyv

U0: inc ecx
U1: cmp ecx, 0
	je KONEC
	mov eax, [ebx]
	mov [ebx], edx
	add ebx, 4
	mov edx, eax
	dec ecx
	jmp U1

U2: mov [ebx], edx
	jmp KONEC

KONEC:
	ret 12
InputElement	endp
;===========================================
	
InputElementCd proc c, Array:dword, N:dword, k:dword

	mov ebx, Array
	mov ecx, N
	mov edx, k
	mov eax, [ebx]
	cmp eax, [ebx+4]
	jg Ubyvanije

Vozrastanije:
	xor eax, eax

	cmp edx, [ebx]
	jl V0

for_Vozr:
	add ebx, 4
	cmp ecx,1
	je V2
	cmp [ebx],edx
	jge V1
	dec ecx
	jmp for_Vozr

V0: inc ecx
V1: cmp ecx, 0
	je KONEC
	mov eax, [ebx]
	mov [ebx], edx
	add ebx, 4
	mov edx, eax
	dec ecx
	jmp V1

V2: mov [ebx], edx
	jmp KONEC

Ubyvanije:
	xor eax, eax

	cmp edx, [ebx]
	jg U0

for_Ubyv:
	add ebx, 4
	cmp ecx,1
	je U2
	cmp [ebx],edx
	jle U1
	dec ecx
	jmp for_Ubyv

U0: inc ecx
U1: cmp ecx, 0
	je KONEC
	mov eax, [ebx]
	mov [ebx], edx
	add ebx, 4
	mov edx, eax
	dec ecx
	jmp U1

U2: mov [ebx], edx
	jmp KONEC

KONEC:
	ret
InputElementCd	endp
;=========================

@InputElementFC@12 proc
push ebp
mov ebx, ecx
mov ecx, edx
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebx]
cmp eax, [ebx+4]
jg Ubyvanije

Vozrastanije:
	xor eax, eax

	cmp edx, [ebx]
	jl V0

for_Vozr:
	add ebx, 4
	cmp ecx,1
	je V2
	cmp [ebx],edx
	jge V1
	dec ecx
	jmp for_Vozr

V0: inc ecx
V1: cmp ecx, 0
	je KONEC
	mov eax, [ebx]
	mov [ebx], edx
	add ebx, 4
	mov edx, eax
	dec ecx
	jmp V1

V2: mov [ebx], edx
	jmp KONEC

Ubyvanije:
	xor eax, eax

	cmp edx, [ebx]
	jg U0

for_Ubyv:
	add ebx, 4
	cmp ecx,1
	je U2
	cmp [ebx],edx
	jle U1
	dec ecx
	jmp for_Ubyv

U0: inc ecx
U1: cmp ecx, 0
	je KONEC
	mov eax, [ebx]
	mov [ebx], edx
	add ebx, 4
	mov edx, eax
	dec ecx
	jmp U1

U2: mov [ebx], edx
	jmp KONEC

KONEC: pop ebp
	ret 4
@InputElementFC@12	endp
	
	end