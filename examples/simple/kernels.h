#pragma once

#include "../../guppy.h"

typedef struct {
    int32_t a, b;
} Input;

gp_kernel(sum_kernel, 256, 1, 1, gp_args(
    gp_global_dim1 length,
    gp_buffer(const Input) input,
    gp_buffer(int32_t) output))
{
    gp_for_tile_in_bounds_1d(length) {
        uint32_t ix = gp_global_index_1d();
        output[ix] = input[ix].a + input[ix].b;
    }
}
