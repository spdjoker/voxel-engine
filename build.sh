#!/bin/bash

# Copy resources
cp -R resources build/resources/

# Build with make
pushd build
make
popd
