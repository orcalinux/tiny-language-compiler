@echo off
:: Compiler and flags
set CXX=g++
set CXXFLAGS=-std=c++17 -Iinclude -Wall -Wextra -Werror

:: Directories
set SRC_DIR=src
set INCLUDE_DIR=include
set BUILD_DIR=build
set OUTPUT_DIR=output

:: Target executable
set TARGET=scanner.exe

:: Create necessary directories if they don't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

:: Compile source files to object files
echo Compiling source files...
for %%f in (%SRC_DIR%\*.cpp) do (
    echo Compiling %%f...
    %CXX% %CXXFLAGS% -c %%f -o "%BUILD_DIR%\%%~nf.o"
)

:: Link object files into the target executable
echo Linking object files...
set OBJS=
for %%f in (%BUILD_DIR%\*.o) do (
    set OBJS=!OBJS! %%f
)
%CXX% %CXXFLAGS% -o %TARGET% %OBJS%

if errorlevel 1 (
    echo Build failed.
    exit /b 1
) else (
    echo Build succeeded.
)

:: Run the scanner with example input and output
if "%1"=="run" (
    echo Running %TARGET% with examples/example1.txt...
    %TARGET% examples/example1.txt %OUTPUT_DIR%\output.txt
    type %OUTPUT_DIR%\output.txt
)

:: Clean up build files and executable
if "%1"=="clean" (
    echo Cleaning up...
    rmdir /s /q "%BUILD_DIR%"
    del "%TARGET%"
    exit /b 0
)


