@echo off
rem --- set A_COMP_PATH=\\10.150.6.2\Common_stud\Kragel\A
set disk=U:
set fpath=%A_COMP_PATH%\masha\d
set spath=%disk%\masha

if not exist %disk% ( echo disk "%disk%" doesn't exist )
else (
	if exist %spath% ( goto end )
	else ( net use %disk% /delete )
)

net use %disk% %fpath% >nul 2 >&1

:end
pause
exit