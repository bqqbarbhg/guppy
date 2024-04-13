#!/usr/bin/env bash
set -e

# Build the example on Linux.

# Create a build directory
mkdir -p build

# Compile main.cpp to build/example
clang++ main.cpp -std=c++14 -pthread -o build/example
