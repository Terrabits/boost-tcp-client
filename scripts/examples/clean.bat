@echo off
setlocal
SET "ROOT_DIR=%~dp0..\.."
cd /d "%ROOT_DIR%"


REM clean
rmdir /S /Q examples\socket\build
del   /Q    examples\socket\CMakeUserPresets.json  >nul  2>&1
