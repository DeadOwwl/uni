@echo off
rem --- set A_COMP_PATH=\\serv604\commons_stud\Kragel\A\
set disk=U:
set fpath=%A_COMP_PATH%\masha\d
set spath=%disk%\masha

if not exist %disk% ( echo disk "%disk%" doesn't exist )
else (
	if exist %spath% ( goto anotherpart )
	else ( net use %disk% /delete )
)

net use %disk% %fpath% >nul 2>&1

:anotherpart
set disk=V:
set fpath=%A_COMP_PATH%\tania\d
set spath=%disk%\tania

if not exist %disk% ( echo disk "%disk%" doesn't exist )
else (
	if exist %spath% ( goto end )
	else ( net use %disk% /delete )
)

net use %disk% %fpath% >nul 2>&1

:end
pause