#pragma once

#include "../../guppy.h"

gp_kernel(count_bytes, 256, 1, 1, gp_args(
	gp_global_dim1 buffer_size,
	gp_buffer(gp_atomic_uint) result,
	gp_buffer(uint8_t) buffer))
{
	gp_shared gp_atomic_uint count[256];

	gp_for_tile() {
		uint32_t li = gp_local_index_1d();
		gp_atomic_store(count[li], 0);
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
		uint32_t num = gp_atomic_load(count[li]);
		if (num != 0) {
			gp_atomic_add(result[li], num);
		}
	}
}

