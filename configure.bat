@echo off
xcopy /s /e /y resources build\resources\
cmake -S . -B build -G "MinGW Makefiles" -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLM_BUILD_TESTS=OFF -DGLM_BUILD_INSTALL=OFF
