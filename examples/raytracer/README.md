# Raytracer

Simple ray tracing example with some spheres.

## Compiling

You only need to compile `main.cpp` to get the example working on the CPU.

```bash
mkdir -p build
clang++ -std=c++14 -O2 -pthread main.cpp -o build/raytracer
```

For GPU backends see the [*guppy_cc*](/examples/guppy_cc) example how to build
the `kernels.gpcc` file. Use any `USE_OPENCL`, `USE_CUDA` and `USE_METAL`
defines when compiling the kernels and the matching `GP_USE_OPENCL`,
`GP_USE_CUDA` and `GP_USE_METAL` defines when compiling `main.cpp`.

```bash
mkdir -p build
python3 ../../guppy_cc.py -D USE_OPENCL kernels.gpcc -o build/kernels.gpcc.h --temp-dir build
clang++ -std=c++14 -O2 -pthread -DGP_USE_OPENCL main.cpp -o build/raytracer
```
