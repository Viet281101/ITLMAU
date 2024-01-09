@echo off
setlocal enabledelayedexpansion

@REM Setting attr
set "inputFile=ex_info.xml"
set "outputFile=ex_info_updated.xml"
set "backupFolder=backup"


@REM Create Backup folder
echo [32mCreating backup folder ...[0m
if not exist !backupFolder! mkdir !backupFolder!
for /f "tokens=2 delims=><" %%a in ('type !inputFile! ^| findstr /C:"<age>"') do (
    set "currentAge=%%a"
)
echo [32mFolder backup created successfully![0m

set /a "newAge=!currentAge!+1"

@REM Date and time setup
set hour=%time:~0,2%
if "%hour:~0,1%" == " " set hour=0%hour:~1,1%
set min=%time:~3,2%
if "%min:~0,1%" == " " set min=0%min:~1,1%
set secs=%time:~6,2%
if "%secs:~0,1%" == " " set secs=0%secs:~1,1%
set year=%date:~-4%
set month=%date:~4,2%
if "%month:~0,1%" == " " set month=0%month:~1,1%
set day=%date:~0,2%
if "%day:~0,1%" == " " set day=0%day:~1,1%

for /f "tokens=1-3 delims=/ " %%b in ('echo %date%') do (
    set "backupDate=%year%%month%%day%"
)
for /f "tokens=1-2 delims=: " %%c in ('echo %time%') do (
    set "backupTime=%hour%h-%min%m-%secs%s"
)

set "backupFileName=!backupFolder!\ex_info_backup_!backupTime!.xml"
copy !inputFile! !backupFileName!


@REM Update Age
(for /f "delims=" %%a in (!inputFile!) do (
    set "line=%%a"
    set "ageTag=<age>"
    set "endTag=</age>"
    setlocal enabledelayedexpansion
    if "!line!" equ "!ageTag!!currentAge!!endTag!" (
        echo ^<age^>!newAge!^</age^>
    ) else (
        echo !line!
    )
    endlocal
)) > !outputFile!

del !inputFile! 
echo [32mOld file cleaned up [0m
move !outputFile! !inputFile!

echo [32mAge updated and file renamed successfully! [0m
echo [32mBackup created :  !backupFileName![0m
@REM timeout /t 1 > nul