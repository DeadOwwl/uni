.686
PUBLIC @DifElFast@8

.model flat
.data
.code

@DifElFast@8 proc 
local a:dword, k:dword

mov ebx, ecx
xor ecx, ecx
mov ecx, edx
xor   eax, eax
mov k, ecx
xor esi, esi
inc esi

C1:
mov eax, [ebx][ecx*4-4]
mov a, eax
mov edx, ecx
dec edx
cmp edx, 0
je E

C2:
mov eax, [ebx][edx*4-4]
cmp a, eax
jge EC2

mov [ebx][ecx*4-4], eax
mov eax, a
mov [ebx][edx*4-4], eax
mov eax, [ebx][ecx*4-4]
mov a, eax

EC2:
dec edx
cmp edx, 0
jne C2

dec ecx
cmp ecx, 0
jne C1

E:
mov ecx, k
inc ecx
mov edx, k

L:
dec edx
dec ecx 
cmp edx, 0
je EN
mov eax, [ebx][ecx*4-4]
mov a, eax
mov eax, [ebx][edx*4-4]

cmp eax, a
je L

inc esi

jmp L

EN:
mov eax, esi
ret 
@DifElFast@8 endp
end