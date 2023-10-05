@echo off
setlocal
SET "ROOT_DIR=%~dp0.."
cd /d "%ROOT_DIR%"


REM clean
call scripts\examples\clean.bat
call scripts\test_package\clean.bat
rmdir /S /Q build
del   /Q    CMakeUserPresets.json  >nul  2>&1
