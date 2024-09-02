
@echo OFF
SETLOCAL EnableExtensions DisableDelayedExpansion
for /F %%a in ('echo prompt $E ^| cmd') do (
  set "ESC=%%a"
)
SETLOCAL EnableDelayedExpansion


echo.
if "%1" == "compile" (
	echo -------- Compiling PFF Project
	msbuild PFF_project.sln /p:Configuration=Debug /p:Platform=x64
) else (
	echo -------- Building PFF Project Solution
	call C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF_editor/../vendor/premake/premake5.exe vs2022
)
echo.

echo -------- Compile Result:
if %errorlevel% neq 0 (
    echo !ESC![31mBUILD FAILED!ESC![0m the premake script encountered [%errorlevel%] errors
) else (
    echo !ESC![32mBUILD SUCCESSFULL!ESC![0m
)

@echo on
