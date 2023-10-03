@echo off
setlocal
SET "ROOT_DIR=%~dp0.."
cd /d "%ROOT_DIR%"


REM clean
rmdir /Q /S build >nul 2>&1
