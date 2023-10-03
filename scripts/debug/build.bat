@echo off
setlocal
SET "ROOT_DIR=%~dp0..\.."
cd /d "%ROOT_DIR%"


REM build
call scripts\build.bat --settings build_type=Debug %*
