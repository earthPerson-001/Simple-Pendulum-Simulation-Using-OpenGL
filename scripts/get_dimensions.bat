@echo off
setlocal

:: Prompt the user for mass
set /p mass="Enter the mass: "

:: Prompt the user for acceleration due to gravity
set /p gravity="Enter the acceleration due to gravity: "

:: Prompt the user for damping factor
set /p damping="Enter the damping factor: "

:: Prompt the user for length of the string
set /p length="Enter the damping factor: "

:: Prompt the user for the starting angle
set /p angle="Enter the starting angle: "

:: Write the values to dimensions.txt in the TEMP directory
set temp_file=%TEMP%\dimensions.txt
(
    echo %mass%
    echo %gravity%
    echo %damping%
    echo %length%
    echo %angle%
) > %temp_file%

echo Dimensions written to %temp_file%
exit
