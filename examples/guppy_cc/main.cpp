#define GP_USE_OPENCL
#define GP_IMPLEMENTATION
#define GP_KERNEL_IMPL

#include "../../guppy.h"

#include <stdio.h>
#include <string.h>

#include "kernels.h"
#include "build/kernels.gpcc.h"

int main(int argc, char **argv)
{
    gp::device_desc desc;
    desc.modules = gpcc_kernels;
    desc.num_modules = gpcc_kernels_count;

    gp::device device = gp::create_device(desc);

    gp::device_info info = device.info();
    printf("Device: %s \"%s\"\n", info.backend, info.device);

    gp::buffer<uint32_t> result = device.create_buffer<uint32_t>(256);

    std::vector<uint8_t> input_data;
    for (size_t i = 0; i < 4096; i++) {
        input_data.push_back((uint8_t)i);
    }

    gp::buffer<uint8_t> input = device.create_buffer<uint8_t>(input_data.size(), input_data.data());

    device.dispatch(count_bytes(
        (uint32_t)input.size(), result, input));

    uint32_t result_data[256];
    result.read(result_data, 0, 256);

    if (gp::error err = device.pop_errors()) {
        fprintf(stderr, "Error: %s\n", err.message());
        return 1;
    }

    for (uint32_t v : result_data) {
        printf("%u ", v);
    }
    printf("\n");

    return 0;
}
