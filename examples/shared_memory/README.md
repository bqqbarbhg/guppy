# Shared memory

Two example kernels using shared memory, one static and one dynamic.

## Compiling

You only need to compile `main.cpp` to get the example working on the CPU.

```bash
mkdir -p build
clang++ -std=c++14 -O2 -pthread main.cpp -o build/shared_memory
```

For GPU backends see the [*guppy_cc*](/examples/guppy_cc) example how to build
the `kernels.gpcc` file. Use any `USE_OPENCL`, `USE_CUDA` and `USE_METAL`
defines when compiling the kernels and the matching `GP_USE_OPENCL`,
`GP_USE_CUDA` and `GP_USE_METAL` defines when compiling `main.cpp`.

```bash
mkdir -p build
python3 ../../guppy_cc.py -D USE_OPENCL kernels.gpcc -o build/kernels.gpcc.h --temp-dir build
clang++ -std=c++14 -O2 -pthread -DGP_USE_OPENCL main.cpp -o build/shared_memory
```

## Using shared memory

Shared memory allows sharing data between threads in a single tile/group.
Each tile sees their own copy of the shared memory.
The amount of shared memory is quite limited, usually the maximum amount per kernel is something between 16kB and 64kB.
Guppy allows requiring a minimum amount of shared memory using `gp::device_desc::shared_memory_size`, defaulting to 16kB,
failing to initialize devices that don't meet the requirement.

### Static shared memory

Using statically allocated shared memory in kernels is easy, just mark any array with the `gp_shared` qualifier.

```cpp
gp_shared uint32_t shared_count[256];
```

This memory is always uninitialized by default for the tile, so it needs to be manually cleared.

```cpp
gp_for_tile() {
    uint32_t li = gp_local_index_1d();
    shared_count[li] = 0;
}
```

After writing to shared memory it can be read by other threads in the group, but to get correct results there needs to be a barrier between usages.

```cpp
gp_tile_sync_shared();
```

Atomic operations are also supported for shared arrays, and can be potentially more efficient than global memory atomic operations.

```cpp
gp_for_tile() {
    uint32_t li = gp_local_index_1d();
    gp_atomic_add(shared_count[li], 1);
}
```

### Dynamic shared memory

Shared memory can also be dynamically allocated at dispatch time, if the amount of shared memory is not know beforehand.
This can also be used to adjust shared memory size depending on the device limits.

To use dynamically sized shared memory buffers they need to be passed as arguments to the kernel.
Due to syntax differences between compute languages the shared buffer must be further initialized via a macro.

```cpp
gp_kernel(my_kernel, 64, 1, 1, gp_args(
    gp_const(uint32_t) shared_size,
    gp_shared_buffer(uint32_t) shared_buffer_ref))
{
    // Expands to
    //   OpenCL:  __local uint32_t* restrict shared_buffer = (__local uint32_t* restrict)(shared_buffer_ref);
    //   CUDA:    uint32_t *p_name = (uint32_t*)(gp_shared_memory + shared_buffer_ref);
    //   Metal:   threadgroup uint32_t *shared_buffer = shared_buffer_ref;
    //   CPU:     ::gp::shared_buffer_view<uint32_t> shared_buffer { ...(shared_buffer_ref) };
    gp_shared_buffer_init(uint32_t, shared_buffer, shared_buffer_ref);

    // Now `shared_buffer` can be used as if it was declared as
    //   gp_shared uint32_t shared_buffer[shared_size];
    gp_for_local_linear_1d(uint32_t, i, shared_size) {
        shared_buffer[i] = 0;
    }
```

To pass a dynamically shared buffer to a kernel you only need the size, as shared buffer contents are always indeterminate.
Shared buffer handles can be initialized in Guppy via `gp::shared_buffer<T>(uint32_t count)`,
these don't use any resources as they're just size information for launching the kernels.

```cpp
uint32_t shared_size = 512;
gp::shared_buffer<uint32_t> shared_buffer { shared_size };

device.dispatch(my_kernel(shared_size, shared_buffer));
```
