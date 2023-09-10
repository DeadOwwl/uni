.model small
 
.stack 100h
 
.data
 
        FileHandle      dw      ?               ;описатель (хэндл) файла
        FileName        db      'KeyLog.txt', 0 ;имя файла для записи кодов клавиш
        FileAttr        dw      00h             ;не ReadOnly, не Hidden,
                                                ; не System, не Archive, не VOLUME_ID
                                                ; не Directory
        ;сообщения программы
        msgPrompt       db      'To exit the program press ESC.', 13, 10, '$'
        ;сообщения об ошибках работы с файлом
        msgErrOpenFile  db      'Error open file', 13, 10, '$'
        msgErrWriteFile db      'Error write file', 13, 10, '$'
        msgErrCloseFile db      'Error close file', 13, 10, '$'
 
        EscAsciiCode    equ     1Bh     ;ASCII код клавиши Esc
 
        ;строка для преобразования числа в строку с 16-ричным представлением
        HexTable        db      '0123456789abcdef'
        ;формируемая строка, которая будет записана в файл
        AmountCodes     equ     16      ;количество кодов, которые будут записаны
                                        ;в каждую строку файла
        StringLen       dw      ?       ;текущая длина строки
        String          db      (AmountCodes*4+1) dup(?)        ;длина строки
                                        ;будет равна количеству кодов на строку
                                        ;умноженному на длину кода (сам код плюс
                                        ;разделитель, а в конце строки вместо разделителя
                                        ;два символа CR и LF)
        CountCode       dw      ?       ;текущее количество обработанных кодов в строке
 
.code
 
;добавляет (дописывает) символ в строку
;вход:
;al - символ для записи
;String, StringLen - глобальные переменные
WriteCharToString       proc
        push    ax
        push    si
        mov     si,     StringLen
        mov     String[si],     al
        inc     word ptr StringLen
        pop     si
        pop     ax
        ret
WriteCharToString       endp
 
;преобразование байта в строку шестнадцатеричного
;представления числа
;вход:
;al    - число для преобразования
;выход
;String, StringLen - в конце строки добавляется строка вида '00h'
HexToStr        proc
        push    ax
        push    bx
        push    cx
        push    dx
 
        mov     bx,     OFFSET HexTable
 
        mov     dx,     ax
 
        and     ax,     00f0h
        mov     cl,     4
        shr     ax,     cl
        xlat
        call    WriteCharToString
 
        mov     ax, dx
 
        and     ax, 000fh
        xlat
        call    WriteCharToString
 
        mov     al,     'h'
        call    WriteCharToString
 
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
HexToStr        endp
 
;запись строки в файл
;вход:
;String, StringLen - глобальные переменные (строка)
;FileHandle - хэндл файла
;выход:
;CY - если установлен, то была ошибка
WriteStringToFile       proc
        push    ax
        push    bx
        push    cx
        push    dx
 
        mov     ah,     40h
        mov     bx,     FileHandle
        lea     dx,     String
        mov     cx,     StringLen
        int     21h
 
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
WriteStringToFile       endp
 
main    proc
        mov     ax,     @data
        mov     ds,     ax
 
        ;сообщение о начале работы программы
        mov     ah,     09h
        lea     dx,     msgPrompt
        int     21h
 
        ;инициализация переменных
        ;строка - пустая, кодов в строке - нет
        mov     ax,     0
        mov     StringLen,      ax
        mov     CountCode,      ax
 
        ;открываем файл для записи
        mov     ah,     3Ch
        mov     cx,     FileAttr
        lea     dx,     FileName
        int     21h
        mov     FileHandle,     ax
        ;если ошибок нет, то перейти к записи кодов в файл
        jnc     @@SaveAllKeyCode
        ;если была ошибка открытия файла,
        ; то вывести сообщение и завершить программу
        mov     ah,     09h
        lea     dx,     msgErrOpenFile
        int     21h
        jmp     @@Exit
 
@@SaveAllKeyCode:
 
        ;читаем один символ с клавиатуры (с ожиданием)
        mov     ah,     00h
        int     16h
 
        ;если нажата клавиша Esc, то завершить цикл
        cmp     al,     EscAsciiCode
        jz      @@FlushFile
 
        ;увеличить переменную, подсчитывающую количество кодов в строке
        inc     word ptr CountCode
        ;если это не первая строка, то поставить разделитель - пробел
        cmp     word ptr CountCode,     1
        je      @@SkipDelimiter
        mov     bx,     ax
        mov     al,     ' '
        call    WriteCharToString
        mov     ax,     bx
@@SkipDelimiter:
        ;добавить к строке код клавиши в hex формате
        call    HexToStr
        ;если это последний код для строки - добавить в конец перевод строки
        ;и записать в файл (в буфер файла)
        cmp     word ptr CountCode,     AmountCodes
        jb      @@SkipWriteToFile
        mov     al,     13
        call    WriteCharToString
        mov     al,     10
        call    WriteCharToString
        call    WriteStringToFile
        mov     word ptr StringLen,     0
        mov     word ptr CountCode,     0
        ;если была ошибка записи в файл,
        ; то вывести сообщение и завершить программу
        jnc     @@SkipWriteToFile
        mov     ah,     09h
        lea     dx,     msgErrWriteFile
        int     21h
        jmp     @@CloseFile
 
@@SkipWriteToFile:
        jmp     @@SaveAllKeyCode
 
@@FlushFile:
        ;дозапись остатков буфера в файл
        call    WriteStringToFile
        mov     word ptr StringLen,     0
        ;если была ошибка записи в файл,
        ; то вывести сообщение и завершить программу
        jnc     @@CloseFile
        mov     ah,     09h
        lea     dx,     msgErrWriteFile
        int     21h
        jmp     @@CloseFile
 
@@CloseFile:
        ;закрытие файла
        mov     ah,     3Eh
        mov     bx,     FileHandle
        int     21h
        ;если ошибок нет, то перейти к завершению программы
        jnc     @@Exit
        ;если была ошибка закрытия файла,
        ; то вывести сообщение и завершить программу
        mov     ah,     09h
        lea     dx,     msgErrCloseFile
        int     21h
 
@@Exit:
        mov     ax,     4C00h
        int     21h
main    endp
end     main