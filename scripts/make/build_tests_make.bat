@ECHO OFF
pushd %~dp0\..\..\
call make tests
popd