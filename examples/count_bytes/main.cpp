#define GP_USE_OPENCL
#define GP_IMPLEMENTATION
#define GP_KERNEL_IMPL

#include <stdio.h>
#include <string.h>

#include "kernels.h"

const char opencl_source[] = R"(
#include "kernels.h"
)";

int main(int argc, char **argv)
{
	gp::module_desc modules[1];

	modules[0].type = gp::module_type::opencl_source;
	modules[0].data = opencl_source;
	modules[0].size = sizeof(opencl_source) - 1;
	modules[0].opts = "-I .";

	gp::device_desc desc;
	desc.modules = modules;
	desc.num_modules = sizeof(modules) / sizeof(*modules);
	desc.num_threads = 1;

	gp::device device = gp::create_device(desc);
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

	return 0;
}
