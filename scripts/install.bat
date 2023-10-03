@echo off
setlocal
SET "ROOT_DIR=%~dp0.."
cd /d "%ROOT_DIR%"


REM install
conan install . --update --build missing %*
