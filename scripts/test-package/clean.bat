@echo off
setlocal
SET "ROOT_DIR=%~dp0..\.."
cd /d "%ROOT_DIR%"


REM clean
rmdir /S /Q test_package\build
del   /Q    test_package\CMakeUserPresets.json  >nul  2>&1
