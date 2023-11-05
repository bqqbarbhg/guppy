#!/usr/bin/env bash
set -e

# Build the example on macOS with Metal support.

# Create a build directory
mkdir -p build

# Compile kernels.gpcc to build/kernels.gpcc.h
# The file itself only declares the platforms and includes "kernels.h"
python3 ../../guppy_cc.py -D USE_METAL kernels.gpcc -o build/kernels.gpcc.h --temp-dir build

# Compile main.cpp to build/example
# We need to build the source as Objective C++ as Metal support in Guppy needs
# it, in a larger project only a single file containing the `GP_IMPLEMENTATION`
# has to be compiled as Objective C++.
clang++ main.cpp -DGP_USE_METAL -std=c++14 -ObjC++ -o build/example \
    -framework Foundation -framework Metal -framework CoreGraphics
