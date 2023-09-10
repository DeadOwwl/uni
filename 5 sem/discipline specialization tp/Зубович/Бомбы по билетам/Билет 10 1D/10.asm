.model small
.data
	file_name db '13.asm',0
	s_file    db '----[ file "13.asm" ]$'
	endline   db 13,10,'$'
	s_pak     db 'Press any key...$'
	buffer    db 81 dup (?)            ;80 + 1 байт для символа конца строки '$'
	handle    dw 1              ;Дескриптор файла
;-------------------------------------------------------------------------------
; Код
.code
start:
    mov ah,3Dh              ;Функция DOS 3Dh (открытие файла)
    xor al,al               ;Режим открытия - только чтение
    mov dx, offset file_name        ;Имя файла
    xor cx,cx               ;Нет атрибутов - обычный файл
    int 21h                 ;Обращение к функции DOS
    mov [handle],ax         ;Сохранение дескриптора файла
 
    mov bx,ax               ;Дескриптор файла
    mov ah,3Fh              ;Функция DOS 3Fh (чтение из файла)
    mov dx, offset buffer           ;Адрес буфера для данных
    mov cx,80               ;Максимальное кол-во читаемых байтов
    int 21h                 ;Обращение к функции DOS
 
     mov bx,offset buffer
    add bx,ax               ;В AX количество прочитанных байтов
    mov byte ptr[bx],'$'        ;Добавление символа '$'
 
    mov ah, 09h
    mov dx, offset s_file
    int 21h                 ;Вывод строки с именем файла
 
    mov cx,56    ;Вывод линии
 
    mov ah,9
    mov dx,offset buffer
    int 21h                 ;Вывод содержимого файла
    mov dx,offset endline
    int 21h                 ;Вывод перехода на новую строку
 
    mov cx,80
 
close_file:
    mov ah,3Eh              ;Функция DOS 3Eh (закрытие файла)
    mov bx,[handle]         ;Дескриптор
    int 21h                 ;Обращение к функции DOS
 
exit:
    mov ah,9
    mov dx,offset s_pak
    int 21h
    
    mov ax,4C00h            ;\
    int 21h                 ;/ Завершение программы
 
end start
