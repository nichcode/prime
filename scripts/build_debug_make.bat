
@ECHO OFF
pushd %~dp0\..\
call make all config=debug
popd