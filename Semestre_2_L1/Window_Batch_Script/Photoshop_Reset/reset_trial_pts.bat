@echo off
setlocal enabledelayedexpansion

@REM :: Local path to the files
set "currentPath=%cd%"
set "localPath=C:\Program Files\Adobe\Adobe Photoshop CS6 (64 Bit)\AMT\"
set "scriptPath=%currentPath%\reset_trial_pts.ps1"
set "logFile=%currentPath%\last_run_time.txt"

@REM :: Check if the log file exists
if exist "%logFile%" (
    set /p lastRunTime=<"%logFile%"
    echo [33mLast Run Time: !lastRunTime! ---- Year:!lastRunTime:~0,4! Month:!lastRunTime:~4,2! Day:!lastRunTime:~6,2! Hour:!lastRunTime:~8,2! Minute:!lastRunTime:~10,2! Second:!lastRunTime:~12,2![0m
    
    @REM :: Get the current date and time
    for /f %%i in ('powershell -command "Get-Date -Format yyyyMMddHHmmss"') do (
        set "currentTime=%%i"
    )
    
    echo [33mCurrent Date and Time: !currentTime! ---- Year:!currentTime:~0,4! Month:!currentTime:~4,2! Day:!currentTime:~6,2! Hour:!currentTime:~8,2! Minute:!currentTime:~10,2! Second:!currentTime:~12,2![0m
    
    @REM :: Calculate the difference between the current time and the last run time
    setlocal enabledelayedexpansion
    set "diff="
    for /f %%i in ('powershell -command "[math]::truncate((Get-Date -Format yyyyMMddHHmmss) - $lastRunTime)"') do (
        set "diff=%%i"
    )
    endlocal
    
    @REM :: Check if 30 days have passed
    if !diff! geq 299999 (
        echo [33mRunning the PowerShell script...[0m
        PowerShell.exe -NoProfile -ExecutionPolicy Bypass -Command "Start-Process PowerShell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File ""%scriptPath%""' -Verb RunAs"
        
        @REM :: Update the log file with new run time
        echo !currentTime! >"%logFile%"
    ) else (
        echo [31mNot enough time has passed. Skipping the script. [0m
    )
) else (
    echo [31mLog file not found. Creating one...  [0m
    
    @REM :: Get the current date and time
    for /f %%i in ('powershell -command "Get-Date -Format yyyyMMddHHmmss"') do (
        set "currentTime=%%i"
    )
    
    @REM :: Run the PowerShell script
    echo [33mRunning the PowerShell script...[0m
    PowerShell.exe -NoProfile -ExecutionPolicy Bypass -Command "Start-Process PowerShell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File ""%scriptPath%""' -Verb RunAs"
    
    @REM :: Save the current time to the log file
    echo !currentTime! >"%logFile%"
)

@REM timeout /t 4 > nul
