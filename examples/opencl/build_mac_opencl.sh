#!/usr/bin/env bash
set -ex

# Build the example on macOS.

# Create a build directory
mkdir -p build

# Compile main.cpp to build/example
clang++ main.cpp -std=c++14 -framework OpenCL -o build/example
