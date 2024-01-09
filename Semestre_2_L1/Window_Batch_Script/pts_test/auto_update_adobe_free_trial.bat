@echo off
setlocal enabledelayedexpansion

@REM :: Local path to the files
set "localPath=C:\Users\Administrateur\Documents\Learn_Batch_Script\pts\"
set "scriptPath=%localPath%update_adobe_trial_serial_nbr.ps1"
set "logFile=%localPath%last_run_time.txt"

@REM :: Check if the log file exists
if exist "%logFile%" (
    set /p lastRunTime=<"%logFile%"
    echo [33mLast Run Time: !lastRunTime![0m
    
    @REM :: Get the current date and time
    for /f %%i in ('powershell -command "Get-Date -Format 'yyyyMMddHHmmss'"') do (
        set "currentTime=%%i"
    )
    
    @REM :: Calculate the difference between the current time and the last run time
    setlocal enabledelayedexpansion
    set "diff="
    for /f %%i in ('powershell -command "[math]::truncate((Get-Date -Format 'yyyyMMddHHmmss') - $lastRunTime)"') do (
        set "diff=%%i"
    )
    endlocal
    
    @REM :: Check if 30 days have passed
    if !diff! geq 300000 (
        echo [33mRunning the PowerShell script...[0m
        PowerShell.exe -NoProfile -ExecutionPolicy Bypass -Command "Start-Process PowerShell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File ""%scriptPath%""' -Verb RunAs"
        
        @REM :: Update the log file with new run time
        echo !currentTime! ---- Year:!currentTime:~0,4! Month:!currentTime:~4,2! Day:!currentTime:~6,2! Hour:!currentTime:~8,2! Minute:!currentTime:~10,2! Second:!currentTime:~12,2!>>"%logFile%"
    ) else (
        echo [31mNot enough time has passed. Skipping the script. [0m
    )
) else (
    echo [31mLog file not found. Creating one...  [0m
    
    @REM :: Get the current date and time
    for /f %%i in ('powershell -command "Get-Date -Format 'yyyyMMddHHmmss'"') do (
        set "currentTime=%%i"
    )
    
    @REM :: Run the PowerShell script
    echo [33mRunning the PowerShell script...[0m
    PowerShell.exe -NoProfile -ExecutionPolicy Bypass -Command "Start-Process PowerShell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File ""%scriptPath%""' -Verb RunAs"
    
    @REM :: Save the current time to the log file
    echo !currentTime! ---- Year:!currentTime:~0,4! Month:!currentTime:~4,2! Day:!currentTime:~6,2! Hour:!currentTime:~8,2! Minute:!currentTime:~10,2! Second:!currentTime:~12,2!>>"%logFile%"
)

timeout /t 2 > nul
