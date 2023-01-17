#pragma once

#include "../../guppy.h"
#include "utils.h"

typedef struct {
    gp_float3 position;
    gp_float3 color;
    float radius;
} Sphere;

typedef struct {
    float distance;
    gp_float3 color;
    gp_float3 normal;
} Hit;

// Interesect against a sphere, updating the hit if necessary
gp_func void intersect(Hit *hit, const Sphere *sphere, Ray ray) {
    float t = intersect_sphere(ray, sphere->position, sphere->radius);
    if (t >= 0.0f && t < hit->distance) {
        gp_float3 position = ray.origin + ray.direction * t;
        hit->normal = rt_normalize(position - sphere->position);
        hit->distance = t;
        hit->color = sphere->color;
    }
}

// Trace rays against spheres for every pixel
gp_kernel(raytrace, 16, 16, 1, gp_args(
    gp_global_dim2 resolution,
    gp_buffer(gp_float3) pixels,
    gp_const(uint32_t) sphere_count,
    gp_buffer(const Sphere) spheres))
{
    gp_for_tile_in_bounds_2d(resolution) {
        gp_uint2 pixel = gp_global_index_2d();

        Ray ray;
        ray.origin = gp_float3(0.0f, 0.0f, -40.0f);
        ray.direction = rt_normalize(gp_float3(
            ((float)pixel.x - (float)resolution.x / 2.0f) / (float)resolution.y,
            ((float)pixel.y - (float)resolution.y / 2.0f) / (float)resolution.y, 1.0f));

        Hit hit;
        hit.distance = 1000.0f;
        hit.color = gp_float3(0.0f, 0.05f, 0.1f) * (ray.direction.y * 0.5f + 0.5f);

        for (uint32_t i = 0; i < sphere_count; i++) {
            intersect(&hit, &spheres[i], ray);
        }

        gp_float3 light = rt_normalize(gp_float3(1.0f, 2.0f, -1.0f));
        gp_float3 col = hit.color * (rt_dot(hit.normal, light) * 0.5f + 0.5f);
        pixels[pixel.y * resolution.x + pixel.x] = col;
    }
}

// Convert floating point pixels to 8-bit sRGB
gp_kernel(to_srgb, 256, 1, 1, gp_args(
    gp_global_dim1 num_pixels,
    gp_buffer(gp_float3) pixels,
    gp_buffer(uint8_t) result))
{
    gp_for_tile_in_bounds_1d(num_pixels) {
        gp_uint ix = gp_global_index_1d();
        gp_float3 pixel = pixels[ix];
        result[ix * 4 + 0] = (uint8_t)gp_min(gp_sqrt(pixel.x) * 256.0f, 255.0f);
        result[ix * 4 + 1] = (uint8_t)gp_min(gp_sqrt(pixel.y) * 256.0f, 255.0f);
        result[ix * 4 + 2] = (uint8_t)gp_min(gp_sqrt(pixel.z) * 256.0f, 255.0f);
        result[ix * 4 + 3] = 0xff;
    }
}
