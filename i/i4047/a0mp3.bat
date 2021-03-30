@echo off
echo "a0mp3.bat: v0.0. 35 "

setlocal ENABLEDELAYEDEXPANSION
call set /a x = 0
for /F "tokens=1,2* delims= "  %%a in ('dir /b track??.mp3') do (
	call set /a x = !x! + 1

	if !x! == 1 (
		rem 	echo !x! : "%%a %%b"
	) 
	ren "%%a %%b" "%%a 0%%b"
)
