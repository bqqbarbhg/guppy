#!/usr/bin/env bash
set -ex

# Build the example on Linux with only CPU support.

# Create a build directory
mkdir -p build

# Compile main.cpp to build/example
clang++ main.cpp -std=c++14 -pthread -o build/example
