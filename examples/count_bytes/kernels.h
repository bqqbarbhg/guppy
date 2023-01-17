#pragma once

#include "../../guppy.h"

gp_kernel(count_bytes, 256, 1, 1, gp_args(
    gp_global_dim1 buffer_size,
    gp_buffer(uint32_t) result,
    gp_buffer(uint8_t) buffer))
{
    gp_shared uint32_t count[256];

    gp_for_tile() {
        uint32_t li = gp_local_index_1d();
        count[li] = 0;
    }

    gp_tile_sync_shared();

    gp_for_tile_in_bounds_1d(buffer_size) {
        uint32_t gi = gp_global_index_1d();
        uint8_t byte = buffer[gi];
        gp_atomic_add(count[byte], 1);
    }

    gp_tile_sync_shared();

    gp_for_tile() {
        uint32_t li = gp_local_index_1d();
        if (count[li] != 0) {
            gp_atomic_add(result[li], count[li]);
        }
    }
}
