
@echo OFF
SETLOCAL EnableExtensions DisableDelayedExpansion
for /F %%a in ('echo prompt $E ^| cmd') do (
  set "ESC=%%a"
)
SETLOCAL EnableDelayedExpansion

REM Change to the project directory
cd /d %~dp0

REM Create metadata and project_files directories
mkdir metadata 2>nul
mkdir metadata\project_files 2>nul

echo.
if "%1" == "compile" (

	echo =================================== Compiling PFF Project ===================================

	echo	-------------------------------- Set up Visual Studio environment ------------------------
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=x64

	echo	---------------------------------------- compile -----------------------------------------
	msbuild PFF_project.sln /p:Configuration=Debug /p:Platform=x64
) else (
	echo =================================== Building PFF Project Solution ===========================
	call C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF_editor/../vendor/premake/premake5.exe vs2022
)
echo.

echo ========================================== Result ===========================================
if %errorlevel% neq 0 (
    echo !ESC![31mBUILD FAILED!ESC![0m the premake script encountered [%errorlevel%] errors
) else (
    echo !ESC![32mBUILD SUCCESSFULL!ESC![0m
)

@echo on
