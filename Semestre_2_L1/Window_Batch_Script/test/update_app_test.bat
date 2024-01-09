@echo off
setlocal enabledelayedexpansion

set "xmlFile=application.xml"
set "newXmlFile=neo_app.xml"
set "targetLine=<Data key=\"TrialSerialNumber\">"

for /f "tokens=*" %%a in ('type !xmlFile! ^| findstr /C:"%targetLine%"') do (
    set "line=%%a"
    set "line=!line:*%targetLine%=!"
    set "line=!line:^<=!"
    set "line=!line:^>=!"
    set "cleanedLine=!line:~44,-7!"
    echo Current trial serial number: [31m !cleanedLine! [0m

    set "powershellCommand=[bigint]::Parse('!cleanedLine!') + 1"
    for /f %%n in ('powershell "!powershellCommand!"') do (
        set "new_serial=%%n"
    )
)

echo Updated trial serial number: [32m !new_serial! [0m

(
    for /f "delims=" %%a in (!xmlFile!) do (
        set "line=%%a"
        setlocal enabledelayedexpansion
        set "serialTag=<Data key=\"TrialSerialNumber\">"
        set "endTag=</Data>"
        if "!line!" equ "    ^<Data key^=\"TrialSerialNumber\"^>!cleanedLine!^</Data^>" (
            echo ^<Data key^="TrialSerialNumber"^>!new_serial!^</Data^>
        ) else (
            echo !line!
        )
        endlocal
    )
) > !newXmlFile!


echo File '!newXmlFile!' created.
exit /b
