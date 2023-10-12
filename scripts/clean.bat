@echo off
setlocal
SET "ROOT_DIR=%~dp0.."
cd /d "%ROOT_DIR%"


REM clean
call  scripts\examples\clean.bat
call  scripts\test_package\clean.bat
rmdir build  /S /Q
rmdir dist   /S /Q
del   CMakeUserPresets.json /Q >nul  2>&1
