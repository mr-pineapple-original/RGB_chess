@echo off
REM Compile main.cpp using g++
g++ -g  source\main.cpp source\player.cpp -o source\main -I"C:\msys64\ucrt64\include" -L"C:\msys64\ucrt64\lib" -lraylib -lopengl32 -lgdi32 -lwinmm 

REM Check if compilation succeeded
if %errorlevel% neq 0 (
    echo.
    echo Compilation failed!
    exit /b %errorlevel%
)

echo.
echo Compilation successful. Running program...
echo.

REM Run the compiled program
.\source\main.exe

echo.