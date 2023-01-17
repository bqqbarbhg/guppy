# OpenCL

Example using OpenCL *without* `guppy_cc.py`. `guppy.h` works when included in
OpenCL and various other kernel languages, so we can just compile `kernels.h`
as an OpenCL kernel without any additional tooling.

## Compiling

To compile the example you must compile `main.cpp` with OpenCL support.
