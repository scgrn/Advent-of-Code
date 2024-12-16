@echo off

setlocal ENABLEEXTENSIONS
setlocal EnableDelayedExpansion

setlocal
for /f "delims=" %%x in (project.cfg) do (set "%%x")

set config=%1
if "%config%" == "debug" (
    call:buildDebug
) else if "%config%" == "release" (
    call:buildRelease
) else if "%config%" == "web-debug" (
    call:buildWebDebug
) else if "%config%" == "web-release" (
    call:buildWebRelease
) else if "%config%" == "assets" (
    call:buildAssets
) else if "%config%" == "dist" (
    call:buildDist
) else if "%config%" == "all" (
    call:buildDebug
    call:buildRelease
    call:buildWebDebug
    call:buildWebRelease
    call:buildAssets
) else (
    echo usage: build config
    echo.
    echo Where config is one of:
    echo.
    echo debug
    echo release
    echo web-debug
    echo web-release
    echo assets
    echo dist
    echo all
)

endlocal
exit /b 0

:buildDebug
    echo Building %PROJECT_NAME% in debug mode...

    md build\debug 2> nul
    cd build\debug
    cmake ..\.. -DCMAKE_BUILD_TYPE=Debug -DPROJECT_NAME=%PROJECT_NAME% -DMUSTARD_DIR=%MUSTARD_PATH% -DSDL2_DIR=%SDL2_PATH%
    cd ..\..
    cmake --build build\debug
exit /b 0

:buildRelease
    echo Building %PROJECT_NAME% in release mode...

    md build\release 2> nul
    cd build\release
    cmake ..\.. -DCMAKE_BUILD_TYPE=Release -DPROJECT_NAME=%PROJECT_NAME% -DMUSTARD_DIR=%MUSTARD_PATH% -DSDL2_DIR=%SDL2_PATH%
    cd ..\..
    cmake --build build\release
exit /b 0

:buildWebDebug
    echo Building %PROJECT_NAME% for web in debug mode...
    
    md build\web-debug 2> nul
    cd build\web-debug
    call emcmake cmake ..\.. -DCMAKE_BUILD_TYPE=Debug -DPROJECT_NAME=%PROJECT_NAME% -DMUSTARD_DIR=%MUSTARD_PATH% -DSDL2_DIR=%SDL2_PATH%
    cd ..\..
    cmake --build build\web-debug
exit /b 0

:buildWebRelease
    echo Building %PROJECT_NAME% for web in release mode...

    md build\web-release 2> nul
    cd build\web-release
    call emcmake cmake ..\.. -DCMAKE_BUILD_TYPE=Release -DPROJECT_NAME=%PROJECT_NAME% -DMUSTARD_DIR=%MUSTARD_PATH% -DSDL2_DIR=%SDL2_PATH%
    cd ..\..
    cmake --build build\web-release
exit /b 0

:buildAssets
    echo Building asset archive...

    set length=64
    set charset=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789
    set ENCRYPTION_KEY=

    for /L %%i in (1,1,%length%) do (
        set /A index=!random! %% 62
        for %%j in (!index!) do set ENCRYPTION_KEY=!ENCRYPTION_KEY!!charset:~%%j,1!
    )

    set MUSTARD_PATH=%MUSTARD_PATH:/=\%
    cd assets
    ..\%MUSTARD_PATH%\bin\Mustard-AssetCompiler ../dist/%PROJECT_NAME%.dat %ENCRYPTION_KEY%
    cd ..

    echo //  Generated by Mustard Engine Build Script > src\addArchive.cpp
    echo //  *** DO NOT MODIFY *** >> src\addArchive.cpp
    echo AB::fileSystem.addArchive("%PROJECT_NAME%.dat", "%ENCRYPTION_KEY%"); >> src\addArchive.cpp
exit /b 0

:buildDist
    echo Building %PROJECT_NAME% for distribution...

    call:buildAssets

    md build\dist 2> nul
    cd build\dist
    cmake ..\.. -DCMAKE_BUILD_TYPE=Dist -DPROJECT_NAME=%PROJECT_NAME% -DMUSTARD_DIR=%MUSTARD_PATH% -DSDL2_DIR=%SDL2_PATH%
    cd ..\..
    cmake --build build\dist
exit /b 0

