@echo off
setlocal
SET "ROOT_DIR=%~dp0.."
cd /d "%ROOT_DIR%"


REM archive
mkdir dist
git archive --output dist\rohdeschwarz-src-0.2.0.zip main
