#pragma once

#include "../../guppy.h"

// Count bytes from `buffer[buffer_size]` to `result[256]`
//
// For example
//
//   buffer { 0, 0, 0, 1, 3, 3 }
//
// Would result in
//
//   result {
//     [0] = 3
//     [1] = 1
//     [3] = 2
//   }
//
gp_kernel(count_bytes, 256, 1, 1, gp_args(
	gp_global_dim1 buffer_size,
	gp_buffer(uint32_t) result,
	gp_buffer(const uint8_t) buffer))
{
	// Statically allocate a shared memory buffer, this buffer is shared for one tile/group
	gp_shared uint32_t count[256];

	// Shared buffers always start in an indeterminate state, so clear the buffer
	gp_for_tile() {
		uint32_t li = gp_local_index_1d();
		count[li] = 0;
	}

	// -- Synchronize for all threads in the tile and shared memory --
	gp_tile_sync_shared();

	// Increment the shared counters for each byte in the input
	gp_for_tile_in_bounds_1d(buffer_size) {
		uint32_t gi = gp_global_index_1d();
		uint8_t byte = buffer[gi];
		gp_atomic_add(count[byte], 1);
	}

	// -- Synchronize for all threads in the tile and shared memory --
	gp_tile_sync_shared();

	// Add the shared counter results to the global result counters
	gp_for_tile() {
		uint32_t li = gp_local_index_1d();
		if (count[li] != 0) {
			gp_atomic_add(result[li], count[li]);
		}
	}
}

// Count sums of `batch_size` bytes from `buffer[buffer_size]` to `result[256 * buffer_size]`
//
// For example
//
//   buffer { 0, 0, 0, 1, 3, 3 }
//   batch_size = 2
//
// Would result in
//
//   result {
//     [0] = 2 // 0+0, 0+0
//     [1] = 1 // 0+1
//     [3] = 1 // 3+0 (end of the array)
//     [4] = 1 // 1+3
//     [6] = 1 // 3+3
//   }
//
// Requires specifying two dynamically sized shared buffers
//   shared_cache = uint32_t[256 + batch_size]
//   shared_count = uint32_t[256 * batch_size]
//
gp_kernel(count_byte_batches, 256, 1, 1, gp_args(
	gp_global_dim1 buffer_size,
	gp_buffer(uint32_t) result,
	gp_buffer(const uint8_t) buffer,
	gp_const(uint32_t) batch_size,
	gp_shared_buffer(uint32_t) shared_cache,
	gp_shared_buffer(uint32_t) shared_count))
{
	const uint32_t cache_size = 256 + batch_size;
	const uint32_t count_size = 256 * batch_size;

	// Initialize a dynamically sized shared buffer passed as an argument.
	//   shared uint32_t cache[cache_size] = &shared_cache
	//   shared uint32_t count[count_size] = &shared_count
	gp_shared_buffer_init(uint32_t, cache, shared_cache);
	gp_shared_buffer_init(uint32_t, count, shared_count);

	// Initialize the shared memory buffers
	gp_for_tile() {
		// Load the next `cache_size` entries to `cache`
		gp_for_local_linear_1d(uint32_t, i, cache_size) {
			uint32_t index = gp_tile_index_1d() * 256 + i;
			cache[i] = index < buffer_size ? buffer[index] : 0;
		}

		// Clear shared `count`
		gp_for_local_linear_1d(uint32_t, i, count_size) {
			count[i] = 0;
		}
	}

	// -- Synchronize for all threads in the tile and shared memory --
	gp_tile_sync_shared();

	// Sum `batch_size` entries in the shared memory cache and increment the local counter
	gp_for_tile() {
		uint32_t li = gp_local_index_1d();
		uint32_t sum = 0;
		for (uint32_t i = 0; i < batch_size; i++) {
			sum += cache[li + i];
		}
		gp_atomic_add(count[sum], 1);
	}

	// -- Synchronize for all threads in the tile and shared memory --
	gp_tile_sync_shared();

	// Add the shared counter results to the global result counters
	gp_for_tile() {
		gp_for_local_linear_1d(uint32_t, i, count_size) {
			if (count[i] != 0) {
				gp_atomic_add(result[i], count[i]);
			}
		}
	}
}
