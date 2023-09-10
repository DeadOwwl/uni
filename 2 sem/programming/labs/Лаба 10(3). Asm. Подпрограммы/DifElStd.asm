.686
PUBLIC DifElStd@8

.model flat
.data
.code

DifElStd@8 proc C, arr:dword, n:dword
local a:dword, k:dword

mov k, esp
xor eax, eax
xor esi, esi
inc esi
mov ebx, arr
mov ecx, n

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
mov ecx, n
inc ecx
mov edx, n

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
ret 8
DifElStd@8 endp
end