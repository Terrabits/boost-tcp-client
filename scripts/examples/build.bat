@echo off
setlocal
SET "ROOT_DIR=%~dp0..\.."
cd /d "%ROOT_DIR%"


REM build socket
cd /d "%ROOT_DIR%\examples\socket"
conan build . %*
