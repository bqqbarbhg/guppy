#!/usr/bin/env bash
set -e

# Build the example on Linux with OpenCL support.

# Create a build directory
mkdir -p build

# Compile kernels.gpcc to build/kernels.gpcc.h
# The file itself only declares the platforms and includes "kernels.h"
python3 ../../guppy_cc.py -D USE_OPENCL kernels.gpcc -o build/kernels.gpcc.h --temp-dir build

# Compile main.cpp to build/example
clang++ main.cpp -DGP_USE_OPENCL -std=c++14 -pthread -lOpenCL -o build/example
