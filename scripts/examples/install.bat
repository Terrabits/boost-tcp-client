@echo off
setlocal
SET "ROOT_DIR=%~dp0..\.."
cd /d "%ROOT_DIR%"


REM install socket
cd /D "%ROOT_DIR%\examples\socket"
conan install . --update --build missing %*
