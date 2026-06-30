@echo off
setlocal enabledelayedexpansion

set GAME_TARGET=Program
set OBJDIR=build
set LOGDIR=logs\debug.log

set CMD=%~1
set CBTYPE=%~2
if "%CBTYPE%"=="" set CBTYPE=Debug

if "%CMD%"=="conf" (
    if exist %OBJDIR% rmdir /s /q %OBJDIR%
    cmake -B %OBJDIR% -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    echo Reconfiguration complete
    goto :eof
)

if "%CMD%"=="build" set CMD=b
if "%CMD%"=="b" (
    cmake --build %OBJDIR% --config %CBTYPE%
    echo Build complete
    goto :eof
)

if "%CMD%"=="run" set CMD=r
if "%CMD%"=="r" (
    if exist "%OBJDIR%\%CBTYPE%\%GAME_TARGET%.exe" (
        :: MSVC build structure
        "%OBJDIR%\%CBTYPE%\%GAME_TARGET%.exe"
    ) else if exist "%OBJDIR%\%GAME_TARGET%.exe" (
        :: MinGW fallback
        "%OBJDIR%\%GAME_TARGET%.exe"
    ) else (
        echo Invalid game target
        exit /b 1
    )
    goto :eof
)

if "%CMD%"=="clean" set CMD=-c
if "%CMD%"=="-c" (
    if exist %OBJDIR% rmdir /s /q %OBJDIR%
    echo Cleaned up binaries
    goto :eof
)

if "%CMD%"=="flush" set CMD=-f
if "%CMD%"=="-f" (
    if exist %LOGDIR% (
        type nul > %LOGDIR%
        echo Flushed %LOGDIR%
    ) else (
        echo %LOGDIR% does not exist
    )
    goto :eof
)

echo Invalid argument
exit /b 1