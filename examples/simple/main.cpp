#include <stdio.h>
#include <assert.h>

#define GP_IMPLEMENTATION
#include "../../guppy.h"

#define GP_KERNEL_IMPL
#include "kernels.h"

int main(int argc, char **argv)
{
    gp::device device = gp::create_device();

    constexpr uint32_t N = 3;
    Input input_values[N] = { { 1, 2 }, { 10, 10 }, { 5, -5 } };

    gp::buffer<Input> input = device.create_buffer<Input>(N, input_values);
    gp::buffer<int32_t> result = device.create_buffer<int32_t>(N);

    device.dispatch(sum_kernel(N, input, result));

    int32_t result_values[N];
    result.read(result_values, 0, N);

    for (uint32_t i = 0; i < N; i++) {
        Input input = input_values[i];
        printf("%d + %d = %d\n", input.a, input.b, result_values[i]);
        assert(input.a + input.b == result_values[i]);
    }

    return 0;
}
