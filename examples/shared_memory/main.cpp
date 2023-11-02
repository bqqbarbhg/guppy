#define _CRT_SECURE_NO_WARNINGS
#define GP_IMPLEMENTATION
#define GP_KERNEL_IMPL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <array>

#include "kernels.h"

// Use external kernels only if some GPU backend is enabled
#if defined(GP_USE_CUDA) || defined(GP_USE_OPENCL) || defined(GP_USE_METAL)
	#define USE_KERNELS
#endif

#if defined(USE_KERNELS)
	#include "build/kernels.gpcc.h"
#endif

int main(int argc, char **argv)
{
	gp::device_desc desc;
	#if defined(USE_KERNELS)
		desc.modules = gpcc_kernels;
		desc.num_modules = gpcc_kernels_count;
	#endif

	gp::device device = gp::create_device(desc);

	std::vector<uint8_t> input_data;
	for (size_t i = 0; i < 1024; i++) {
		input_data.push_back(uint8_t(i));
	}

	gp::buffer<uint8_t> input = device.create_buffer<uint8_t>(input_data.size(), input_data.data());

	// Count bytes using static shared memory
	{
		gp::buffer<uint32_t> result = device.create_buffer<uint32_t>(256);

		std::array<uint32_t, 256> result_reference { };
		for (uint8_t b : input_data) {
			result_reference[b] += 1;
		}

		device.dispatch(count_bytes((uint32_t)input.size(), result, input));

		std::array<uint32_t, 256> result_data { };
		result.read(result_data.data(), 0, result_data.size());
		assert(result_data == result_reference);
	}

	// Count batches of bytes using dynamic shared memory
	{
		uint32_t batch_size = 3;

		uint32_t cache_size = 256 + batch_size;
		uint32_t count_size = 256 * batch_size;
		gp::buffer<uint32_t> result = device.create_buffer<uint32_t>(count_size);

		gp::shared_buffer<uint32_t> shared_cache { cache_size };
		gp::shared_buffer<uint32_t> shared_count { count_size };
		device.dispatch(count_byte_batches((uint32_t)input.size(),
			result, input, batch_size, shared_cache, shared_count));

		std::vector<uint32_t> result_reference(count_size);
		std::vector<uint32_t> result_data(count_size);

		for (size_t begin = 0; begin < input_data.size(); begin++) {
			uint32_t sum = 0;
			for (uint32_t i = 0; i < batch_size; i++) {
				size_t index = begin + i;
				sum += index < input_data.size() ? input_data[index] : 0u;
			}
			result_reference[sum] += 1;
		}

		result.read(result_data.data(), 0, result_data.size());
		assert(result_data == result_reference);
	}

	return 0;
}
