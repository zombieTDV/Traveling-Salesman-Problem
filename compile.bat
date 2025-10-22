@echo off
setlocal enabledelayedexpansion

:menu
cls
echo ================================
echo    C++ Project Build System
echo ================================
echo 1. Build Project
echo 2. Clean Build Files
echo 3. Run Program
echo 4. Test Program
echo 5. Exit
echo ================================
set /p choice="Enter your choice (1-5): "

if "%choice%"=="1" goto build
if "%choice%"=="2" goto clean
if "%choice%"=="3" goto run
if "%choice%"=="4" goto test
if "%choice%"=="5" goto end

echo Invalid choice! Please try again.
timeout /t 2 >nul
goto menu

:build
echo.
echo Building project...
g++ -Wall -Wextra src/*.cpp -o program
if %errorlevel% equ 0 (
    echo.
    echo Build successful! ^(No errors or warnings^)
) else (
    echo.
    echo Build failed! Please check the errors above.
)
pause
goto menu

:clean
echo.
echo Cleaning build files...
if exist program.exe del program.exe
if exist *.o del *.o
echo Clean complete!
pause
goto menu

:run
echo.
if exist program.exe (
    program.exe
) else (
    echo Program not found! Please build first.
)
pause
goto menu

:test
echo Building project...
g++ -Wall -Wextra tests/*.cpp -o unitTest
if %errorlevel% equ 0 (
    echo.
    echo Build successful! ^(No errors or warnings^)
) else (
    echo.
    echo Build failed! Please check the errors above.
)
if exist unitTest.exe (
    unitTest.exe
) else (
    echo Unit test not found! Please build first.
)
pause
goto menu

:end
echo Goodbye!
timeout /t 1 >nul
exit 