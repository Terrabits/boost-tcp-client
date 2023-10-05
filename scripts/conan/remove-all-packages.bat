@echo off
setlocal
SET "ROOT_DIR=%~dp0..\.."
cd /d "%ROOT_DIR%"


REM remove all packages
conan cache clean --source --build --download --temp
conan remove "*" --confirm >nul
