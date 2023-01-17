#include <stdio.h>
#include <assert.h>

#define GP_USE_OPENCL
#define GP_IMPLEMENTATION
#include "../../guppy.h"

#define GP_KERNEL_IMPL
#include "kernels.h"

int main(int argc, char **argv)
{
    // Read `kernels.h` at runtime to `kernel_data`, ideally we'd use `#embed`
    // here if it would be available.
    static char kernel_data[32*4096];
    FILE *kernel_file = fopen("kernels.h", "r");
    size_t kernel_size = fread(kernel_data, 1, sizeof(kernel_data), kernel_file);
    fclose(kernel_file);

    // Modules are backend-specific kernel binaries/sources, here we just supply
    // the `kernels.h` source as-is as it compiles as OpenCL. We need to supply
    // the option "-I ." so that OpenCL can resolve `#include "../../guppy.h"
    gp::module_desc modules[1];
    modules[0].type = gp::module_type::opencl_source;
    modules[0].data = kernel_data;
    modules[0].size = kernel_size;
    modules[0].opts = "-I .";

    // Create the device with the modules.
    gp::device_desc desc;
    desc.modules = modules;
    desc.num_modules = 1;
    gp::device device = gp::create_device(desc);

    constexpr uint32_t N = 4096;
    gp::buffer<uint32_t> result = device.create_buffer<uint32_t>(N);

    device.dispatch(generate_squares(N, result));

    uint32_t result_values[N];
    result.read(result_values, 0, N);
    for (uint32_t i = 0; i < N; i++) {
        assert(result_values[i] == i * i);
    }

    return 0;
}
