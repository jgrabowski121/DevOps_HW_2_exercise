@echo off

rem exercise8_2.bat
rem Justin Grabowski
rem 
rem This file will test if H2.3.exe exists, 
rem  and if it exists then the exe will be run
rem  If the return value of H2.3.exe is 0 then it 
rem  will be copied to the doployment folder

setlocal ENABLEDELAYEDEXPANSION

if exist ".\Exercise8_2_H2_3\Debug\HW2.3.exe" (
    ".\Exercise8_2_H2_3\Debug\HW2.3.exe" 
    echo !errorlevel!
    if !errorlevel! == 0 (
        copy ".\Ex_8_H2_2\Debug\H2_2.exe" ".\Release\"
        echo H2.2 deployed
    ) else (
        echo Unit tests failed
    )
) else (
    echo H2.3 does not exist
)

pause