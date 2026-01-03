@echo off
setlocal enabledelayedexpansion

set CXX=g++
set SRC_DIR=source
set OUT=source\main.exe

set INCLUDE=C:\msys64\ucrt64\include
set LIB=C:\msys64\ucrt64\lib

set SOURCES=

for %%f in (%SRC_DIR%\*.cpp) do (
    set SOURCES=!SOURCES! %%f
)

%CXX% -g %SOURCES% ^
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

