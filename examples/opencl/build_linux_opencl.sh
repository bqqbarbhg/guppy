#!/usr/bin/env bash
set -e

# Build the example on Linux with only OpenCL support.

# Create a build directory
mkdir -p build

# Compile main.cpp to build/example
clang++ main.cpp -std=c++14 -pthread -lOpenCL -o build/example
