@ECHO OFF
pushd %~dp0\..\
call make clean
del /S *Makefile
popd
PAUSE