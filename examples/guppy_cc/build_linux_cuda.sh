#!/usr/bin/env bash
set -ex

# Build the example on Linux with OpenCL and CUDA support.

# Create a build directory
mkdir -p build

# Compile kernels.gpcc to build/kernels.gpcc.h
# The file itself only declares the platforms and includes "kernels.h"
python3 ../../guppy_cc.py -D USE_CUDA kernels.gpcc -o build/kernels.gpcc.h --temp-dir build

# Compile main.cpp to build/example
# TEMP HACK
clang++ main.cpp -DGP_USE_CUDA -std=c++14 -pthread -lOpenCL -lcuda -o build/example
