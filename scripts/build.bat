@echo off
setlocal
SET "ROOT_DIR=%~dp0.."
cd /d "%ROOT_DIR%"


REM build
conan build . %*
