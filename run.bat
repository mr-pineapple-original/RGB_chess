@echo off
setlocal

REM Compiler
set CXX=g++

REM Paths
set SRC=source
set OUT=source\main.exe

REM Raylib paths (MSYS2 ucrt64)
set INCLUDE=C:\msys64\ucrt64\include
set LIB=C:\msys64\ucrt64\lib

REM Compile all cpp files in source/
%CXX% -g %SRC%\*.cpp ^
    -I"%INCLUDE%" ^
    -L"%LIB%" ^
    -lraylib -lopengl32 -lgdi32 -lwinmm ^
    -o %OUT%

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo Compilation failed!
    exit /b %ERRORLEVEL%
)

echo.
echo Compilation successful. Running program...
echo.

%OUT%

endlocal

