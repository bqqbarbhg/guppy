#!/usr/bin/env bash
set -ex

# Build the example on macOS with OpenCL support.

# Create a build directory
mkdir -p build

# Compile kernels.gpcc to build/kernels.gpcc.h
# The file itself only declares the platforms and includes "kernels.h"
python3 ../../guppy_cc.py kernels.gpcc -D USE_OPENCL -o build/kernels.gpcc.h --temp-dir build

# Compile main.cpp to build/example
clang++ main.cpp -DGP_USE_OPENCL -std=c++14 -framework OpenCL -o build/example
