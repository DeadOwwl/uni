@echo off

rem --- set B_COMP_PATH=\\serv604\commons_stud\Kragel\A\
set path1=%B_COMP_PATH%\first
set path2=%B_COMP_PATH%\second
set path3=%B_COMP_PATH%\third

	if not exist %path1% (md %path1%)
	if not exist %path1%\common\Progects (
		md %path1%\common\Progects\1
		md %path1%\common\Progects\2
	)
	if not exist %path1%\common\Progects\1 (md %path1%\common\Progects\1)
	if not exist %path1%\common\Progects\2 (md %path1%\common\Progects\2)	
	if not exist %path1%\copies (md %path1%\copies)

	if not exist %path2% (md %path2%)
	if not exist %path2%\d\"Мои документы" (md %path2%\d\"Мои документы")
	if not exist %path2%\e\myprog (md %path2%\e\myprog\data)
        if not exist %path2%\e\myprog\data (md %path2%\e\myprog\data)
	if not exist %path2%\copies (md %path2%\copies)
        if not exist %path2%\copies\first_last_copy (md %path2%\copies\first_last_copy)

        if not exist %path3% (md %path3%)
	if not exist %path3%\e (md %path3%\e)
	if not exist %path3%\copies (md %path3%\copies)
	if not exist %path3%\copies\first_previous_copy (md %path3%\copies\first_previous_copy)

set comp2=%B_COMP_PATH%\second\copies\first_last_copy
set comp3=%B_COMP_PATH%\third\copies\first_previous_copy 
set dest=%comp2%

if not exist %comp2% (
 call :COPY1
 set dest=%comp3%
 call :COPY1
 goto :part2
)else (
  rmdir %comp3% /s /q >nul 2>&1
  xcopy %comp2%  %comp3% /e /i /y >nul
  rmdir %comp2% /s /q >nul 2>&1
  call :COPY1
  goto :part2
) 

:COPY1
xcopy %path1%\common\Progects\1 %dest%\Progects\1 /i /y >nul 2>&1
xcopy %path1%\common\Progects\2 %dest%\Progects\2 /i /y >nul 2>&1
exit /b

:part2
set comp1=%B_COMP_PATH%\first\copies\second_last_copy
set comp3=%B_COMP_PATH%\third\copies\second_previous_copy 

set dest=%comp1%
set flag=0

if exist %comp1% (
  rmdir %comp3% /s /q >nul 2>&1
  xcopy %comp1% %comp3% /e /i /y >nul
  rmdir %comp1% /s /q >nul 2>&1
  call :COPY2
  goto :end 
) else (
 call :COPY2
 set dest=%comp3%
 call :COPY2
 goto :end
)

:COPY2
xcopy %path2%\d\"Мои документы" %dest%\"Мои документы" /e /i /y >nul 2>&1
xcopy %path2%\e\myprog\data %dest%\myprog\data /i /y >nul 2>&1
exit /b
:end
echo Done B.bat...    
pause               