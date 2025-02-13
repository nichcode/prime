@ECHO OFF
pushd %~dp0\..\
call make prime CC=g++
popd