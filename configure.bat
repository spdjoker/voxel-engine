@echo off

REM Populate git submodules
git submodule update --init --recursive

REM Configure cmake
cmake -S . -B build -G "MinGW Makefiles" -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLM_BUILD_TESTS=OFF -DGLM_BUILD_INSTALL=OFF -Dglew-cmake_BUILD_SHARED=OFF
