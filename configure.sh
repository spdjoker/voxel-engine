#!/bin/bash

# Populate git submodules
git submodule update --init --recursive

# Configure cmake
cmake -S . -B build -G "Unix Makefiles" \
  -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF \
  -DGLFW_BUILD_TESTS=OFF -DGLM_BUILD_TESTS=OFF \
  -DGLM_BUILD_INSTALL=OFF -Dglew-cmake_BUILD_SHARED=OFF

