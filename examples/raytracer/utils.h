#pragma once

typedef struct {
	gp_float3 origin;
	gp_float3 direction;
} Ray;

static gp_func gp_float rt_dot(gp_float3 a, gp_float3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

static gp_func gp_float3 rt_normalize(gp_float3 v) {
	return v / gp_sqrt(rt_dot(v, v));
}

static gp_func float intersect_sphere(Ray ray, gp_float3 position, float radius) {
	gp_float3 delta = ray.origin - position;
	float a = rt_dot(ray.direction, ray.direction);
	float b = 2.0f * rt_dot(delta, ray.direction);
	float c = rt_dot(delta, delta) - radius*radius;
	float radicand = b*b - 4.0f*a*c;
	if (radicand <= 0.0f) return -1.0f;
	float root = gp_sqrt(radicand);
	float denom = 0.5f / a;
	if ((-b + root) * denom < 0.0f) return -1.0f;
	return gp_max(0.0f, (-b - root) * denom);
}

