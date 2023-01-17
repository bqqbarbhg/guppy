#include "../../guppy.h"

gp_kernel(generate_squares, 256, 1, 1, gp_args(
    gp_global_dim1 result_size,
    gp_buffer(uint32_t) result))
{
    gp_for_tile_in_bounds_1d(result_size) {
        uint32_t index = gp_global_index_1d();
        result[index] = index * index;
    }
}
