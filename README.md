# Guppy

Guppy is a single header library that aims to make GPGPU programming
approachable and allows you to debug kernels on CPU.

Supported backends:

- CPU
- OpenCL
- CUDA
- Metal

## Getting started

Copy `guppy.h` to your project and in a single file define the following to
generate an implementation:

```c
// #define GP_USE_OPENCL // for OpenCL support
// #define GP_USE_CUDA   // for CUDA support
// #define GP_USE_METAL  // for Metal support
#define GP_IMPLEMENTATION
#include "guppy.h"
```

## Writing kernels

Guppy kernels are written in C, restricted by what platforms you want to support.
CPU supports all of C++, CUDA, and Metal support most of C++ and OpenCL is quite
strict "shader-like" C.

You can place kernels in a file such as `my_kernels.h`, which should `#include`
`guppy.h`. This file can then be compiled as C++ / CUDA / OpenCL / Metal.
`guppy.h` defines macros to make the kernels portable accross the various
backends.

The programming model is a bit strange to support both CPU and GPU for the same
kernel. Code at top-level scope is executed only once on CPU but for all threads
simultaneously on GPU. To fork we must use `gp_for_tile()` which runs the body
for each work group element (loop on CPU, no-op on GPU).

```cpp
gp_kernel(increment_list,
    // Thread group size
    256, 1, 1,
    // Arguments passed from the CPU to the kernel
    gp_args(
        // `gp_global_dim1` implicitly adjusts the dispatch size based on this,
        // eg. `data_size=1000` would dispatch 4x 256x1x1 groups.
        gp_global_dim1 data_size,
        // Pointer to some values, ie. `uint32_t *values` on GPU
        gp_buffer(uint32_t) data))
{
    // Loop over the 256x1x1 group
    gp_for_tile() {
        // Get the global index, ie. `group.x * 256 + local.x`
        uint32_t index = gp_local_index_1d();
        
        // Note that the dispatch is rounded up to group size so some indices
        // might be past our input size, for convenience we could use
        // `gp_for_tile_in_bounds_1d(data_size)` instead.
        if (index < data_size) {
            data[index] += 1;
        }
    }
}
```

For executing serial code (opposite of `gp_for_tile()`) we can use
`gp_once_per_tile_Nd()` which executes the body only for the first thread in the
group.

```cpp
gp_kernel(sum, 256, 1, 1,
    gp_args(
        gp_global_dim1 input_size,
        gp_buffer(const uint32_t) input,
        gp_buffer(uint32_t) result))
{
    // Thread group local counter
    gp_shared gp_atomic_uint group_sum;

    // Reset the atomic sum to zero
    gp_once_per_tile_1d() {
        gp_atomic_store(group_sum, 0);
    }

    // Sum all the values in the input to the local accumulator
    gp_for_tile_in_bounds_1d(data_size) {
        gp_atomic_add(group_sum, data[gp_local_index_1d()]);
    }

    // Add the group local counter to the global one
    gp_once_per_tile_1d() {
        gp_atomic_add(result[0], gp_atomic_load(group_sum));
    }
}
```

See [kernel.md](docs/kernel.md) for further information about the kernel
programming environment.

## Calling kernels

The kernels are included as normal header files when compiling the program so
we can call them via their names using `gp::device::dispatch()`. The header
might be included in multiple files but a single one must define `GP_KERNEL_IMPL`
before including it to generate the CPU function bodies.
