del mkvlist.txt
rem ------------ echo mkvc.bat v0.0. 33 ;           >>      mkvlist.txt

rem step1: replace space with ''
@echo on
setlocal ENABLEDELAYEDEXPANSION
for %%a in ("* *.mkv") do (
set file=%%a
ren "!file!" "!file: =!"

)

rem ----------- step2: write list to mkvlist.txt

call set /a x = 0
for /F "delims=" %%a in ('dir /b *.mkv') do (
call set /a x = !x! + 1
rem echo !x!
echo file '%%a'                                     >>      mkvlist.txt
)
@echo off


rem -------- step3 ----- run ffmpeg command
ffmpeg -f concat -i mkvlist.txt -c copy all.mkv