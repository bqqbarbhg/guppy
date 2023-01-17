#define _CRT_SECURE_NO_WARNINGS
#define GP_IMPLEMENTATION
#define GP_KERNEL_IMPL

#include <stdio.h>
#include <string.h>

#include "kernels.h"
#include "bmp.h"

// Use external kernels only if some GPU backend is enabled
#if defined(GP_USE_OPENCL) || defined(GP_USE_OPENCL) || defined(GP_USE_METAL)
	#define USE_KERNELS
#endif

#if defined(USE_KERNELS)
	#include "build/kernels.gpcc.h"
#endif

float random() { return (float)rand() / (float)RAND_MAX; }
gp_float2 random2() { return gp_float2(random(), random()); }
gp_float3 random3() { return gp_float3(random(), random(), random()); }

int main(int argc, char **argv)
{
	gp::device_desc desc;
	#if defined(USE_KERNELS)
		desc.modules = gpcc_kernels;
		desc.num_modules = gpcc_kernels_count;
	#endif

	gp::device device = gp::create_device(desc);

	// Initialize random spheres
	std::vector<Sphere> sphere_data;
	for (uint32_t i = 0; i < 64; i++) {
		Sphere sphere;
		sphere.position = (random3() * 2.0f - gp_float3(1.0f, 1.0f, 1.0f)) * gp_float3(30.0f, 20.0f, 15.0f);
		sphere.radius = 1.0f + random() * 3.0f;
		sphere.color = random3();
		sphere_data.push_back(sphere);
	}

	// Upload the generated spheres to GPU
	gp::buffer<Sphere> spheres = device.create_buffer<Sphere>(sphere_data.size(), sphere_data.data());

	// Create an empty buffer of pixels
	gp_uint2 resolution = gp_uint2(1280, 720);
	uint32_t num_pixels = resolution.x * resolution.y;
	gp::buffer<gp_float3> pixels = device.create_buffer<gp_float3>(num_pixels);

	// Raytrace against the spheres
	device.dispatch(raytrace(resolution, pixels, (uint32_t)spheres.size(), spheres));

	// Convert the float pixels to 8-bit sRGB
	gp::buffer<uint8_t> srgb = device.create_buffer<uint8_t>(num_pixels * 4);
	device.dispatch(to_srgb(num_pixels, pixels, srgb));

	// Read the result back from the GPU
	std::vector<uint8_t> result(num_pixels * 4);
	srgb.read(result.data(), 0, result.size());

	// Write the picture as a .bmp
	{
		FILE *f = fopen("output.bmp", "wb");
		BmpHeaderRgba header{resolution.x, resolution.y};
		fwrite(&header, 1, sizeof(header), f);
		fwrite(result.data(), 1, result.size(), f);
		fclose(f);
	}

	return 0;
}
