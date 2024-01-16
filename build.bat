@echo off

REM Copy resources
xcopy /s /e /y resources build\resources\

REM Build with make
pushd build
make
popd
