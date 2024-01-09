@REM @echo off

@REM setlocal enabledelayedexpansion

@REM set "xml_file=ex_info.xml"
@REM set "temp_file=temp.xml"
@REM set "search_line=<age>"
@REM set "replacement_line=<age>"

@REM for /f "usebackq tokens=*" %%a in (!xml_file!) do (
@REM     set "line=%%a"
@REM     if "!line!"=="" (
@REM         echo.>>!temp_file!
@REM     ) else if "!line!" equ "!search_line!" (
@REM         for %%b in (!line!) do (
@REM             set /a "new_age=%%~nb+1"
@REM             echo !replacement_line!%%new_age%</age> >> !temp_file!
@REM         )
@REM     ) else (
@REM         echo !line!>>!temp_file!
@REM     )
@REM )

@REM move /y !temp_file! !xml_file!

@REM endlocal




@echo off
@REM python update_age.py
pyinstaller --onefile update_age.py