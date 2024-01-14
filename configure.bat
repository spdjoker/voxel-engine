@echo off
xcopy /s /e /y resources build\resources\
cmake -S . -B build -G "MinGW Makefiles"
