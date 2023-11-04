#ifndef GP_INCLUDED
#define GP_INCLUDED

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused"
    #pragma GCC diagnostic ignored "-Wattributes"
#endif

#if defined(__CUDACC__)
    #define gp_func __device__
#else
    #define gp_func
#endif

#if defined(_MSC_VER)
#define gp_forceinline __forceinline
#define gp_noinline __declspec(noinline)
#define gp_restrict __restrict
#define gp_template_restrict __restrict
#elif defined(__GNUC__)
#define gp_forceinline __attribute__((always_inline))
#define gp_noinline __attribute__((noinline))
#define gp_restrict __restrict
#define gp_template_restrict
#elif defined(__NVCC__)
#define gp_forceinline __forceinline__
#define gp_noinline __noinline__
#define gp_restrict __restrict__
#define gp_template_restrict
#else
#define gp_forceinline
#define gp_noinline
#define gp_restrict
#define gp_template_restrict
#endif

#if !(defined(GP_OPENCL_SOURCE) || defined(__OPENCL_VERSION__)) && !(defined(GP_METAL_SOURCE) || defined(__METAL_VERSION__))

#include <stdint.h>
#include <math.h>

#ifndef GP_USE_SSE
#if (defined(_MSC_VER) && (defined(_M__IX86) || defined(_M_X64))) || (defined(__GNUC__) && (defined(__i386__) || defined(__amd64__)))
    #include <xmmintrin.h>
    #include <emmintrin.h>
    #define GP_USE_SSE
#endif
#endif

typedef float gp_float;
typedef int32_t gp_int;
typedef uint32_t gp_uint;

struct alignas(8) gp_float2 {
    float x, y;
    gp_func constexpr gp_float2() : x(0.0f), y(0.0f) { }
    gp_func constexpr gp_float2(float x, float y) : x(x), y(y) { }
    gp_func gp_float2 operator+(const gp_float2 &r) const { return gp_float2(x + r.x, y + r.y); }
    gp_func gp_float2 &operator+=(const gp_float2 &r) { x += r.x; y += r.y; return *this; }
    gp_func gp_float2 operator-(const gp_float2 &r) const { return gp_float2(x - r.x, y - r.y); }
    gp_func gp_float2 &operator-=(const gp_float2 &r) { x -= r.x; y -= r.y; return *this; }
    gp_func gp_float2 operator*(const gp_float2 &r) const { return gp_float2(x * r.x, y * r.y); }
    gp_func gp_float2 &operator*=(const gp_float2 &r) { x *= r.x; y *= r.y; return *this; }
    gp_func gp_float2 operator/(const gp_float2 &r) const { return gp_float2(x / r.x, y / r.y); }
    gp_func gp_float2 &operator/=(const gp_float2 &r) { x /= r.x; y /= r.y; return *this; }
    gp_func gp_float2 operator*(float r) const { return gp_float2(x * r, y * r); }
    gp_func gp_float2 &operator*=(float r) { x *= r; y *= r; return *this; }
    gp_func gp_float2 operator/(float r) const { return gp_float2(x / r, y / r); }
    gp_func gp_float2 &operator/=(float r) { x /= r; y /= r; return *this; }
};

struct alignas(16) gp_float3 {
    float x, y, z;
    gp_func constexpr gp_float3() : x(0.0f), y(0.0f), z(0.0f) { }
    gp_func constexpr gp_float3(float x, float y, float z) : x(x), y(y), z(z) { }
    gp_func gp_float3 operator+(const gp_float3 &r) const { return gp_float3(x + r.x, y + r.y, z + r.z); }
    gp_func gp_float3 &operator+=(const gp_float3 &r) { x += r.x; y += r.y; z += r.z; return *this; }
    gp_func gp_float3 operator-(const gp_float3 &r) const { return gp_float3(x - r.x, y - r.y, z - r.z); }
    gp_func gp_float3 &operator-=(const gp_float3 &r) { x -= r.x; y -= r.y; z -= r.z; return *this; }
    gp_func gp_float3 operator*(const gp_float3 &r) const { return gp_float3(x * r.x, y * r.y, z * r.z); }
    gp_func gp_float3 &operator*=(const gp_float3 &r) { x *= r.x; y *= r.y; z *= r.z; return *this; }
    gp_func gp_float3 operator/(const gp_float3 &r) const { return gp_float3(x / r.x, y / r.y, z / r.z); }
    gp_func gp_float3 &operator/=(const gp_float3 &r) { x /= r.x; y /= r.y; z /= r.z; return *this; }
    gp_func gp_float3 operator*(float r) const { return gp_float3(x * r, y * r, z * r); }
    gp_func gp_float3 &operator*=(float r) { x *= r; y *= r; z *= r; return *this; }
    gp_func gp_float3 operator/(float r) const { return gp_float3(x / r, y / r, z / r); }
    gp_func gp_float3 &operator/=(float r) { x /= r; y /= r; z /= r; return *this; }
};

struct alignas(16) gp_float4 {
    float x, y, z, w;
    gp_func constexpr gp_float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    gp_func constexpr gp_float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
    gp_func gp_float4 operator+(const gp_float4 &r) const { return gp_float4(x + r.x, y + r.y, z + r.z, w + r.w); }
    gp_func gp_float4 &operator+=(const gp_float4 &r) { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }
    gp_func gp_float4 operator-(const gp_float4 &r) const { return gp_float4(x - r.x, y - r.y, z - r.z, w - r.w); }
    gp_func gp_float4 &operator-=(const gp_float4 &r) { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }
    gp_func gp_float4 operator*(const gp_float4 &r) const { return gp_float4(x * r.x, y * r.y, z * r.z, w * r.w); }
    gp_func gp_float4 &operator*=(const gp_float4 &r) { x *= r.x; y *= r.y; z *= r.z; w *= r.w; return *this; }
    gp_func gp_float4 operator/(const gp_float4 &r) const { return gp_float4(x / r.x, y / r.y, z / r.z, w / r.w); }
    gp_func gp_float4 &operator/=(const gp_float4 &r) { x /= r.x; y /= r.y; z /= r.z; w /= r.w; return *this; }
    gp_func gp_float4 operator*(float r) const { return gp_float4(x * r, y * r, z * r, w * r); }
    gp_func gp_float4 &operator*=(float r) { x *= r; y *= r; z *= r; w *= r; return *this; }
    gp_func gp_float4 operator/(float r) const { return gp_float4(x / r, y / r, z / r, w / r); }
    gp_func gp_float4 &operator/=(float r) { x /= r; y /= r; z /= r; w /= r; return *this; }
};

struct alignas(8) gp_int2 {
    int32_t x, y;
    gp_func constexpr gp_int2() : x(0), y(0) { }
    gp_func constexpr gp_int2(int32_t x, int32_t y) : x(x), y(y) { }
    gp_func gp_int2 operator+(const gp_int2 &r) const { return gp_int2(x + r.x, y + r.y); }
    gp_func gp_int2 &operator+=(const gp_int2 &r) { x += r.x; y += r.y; return *this; }
    gp_func gp_int2 operator-(const gp_int2 &r) const { return gp_int2(x - r.x, y - r.y); }
    gp_func gp_int2 &operator-=(const gp_int2 &r) { x -= r.x; y -= r.y; return *this; }
    gp_func gp_int2 operator*(const gp_int2 &r) const { return gp_int2(x * r.x, y * r.y); }
    gp_func gp_int2 &operator*=(const gp_int2 &r) { x *= r.x; y *= r.y; return *this; }
    gp_func gp_int2 operator/(const gp_int2 &r) const { return gp_int2(x / r.x, y / r.y); }
    gp_func gp_int2 &operator/=(const gp_int2 &r) { x /= r.x; y /= r.y; return *this; }
    gp_func gp_int2 operator*(int32_t r) const { return gp_int2(x * r, y * r); }
    gp_func gp_int2 &operator*=(int32_t r) { x *= r; y *= r; return *this; }
    gp_func gp_int2 operator/(int32_t r) const { return gp_int2(x / r, y / r); }
    gp_func gp_int2 &operator/=(int32_t r) { x /= r; y /= r; return *this; }
};

struct alignas(16) gp_int3 {
    int32_t x, y, z;
    gp_func constexpr gp_int3() : x(0), y(0), z(0) { }
    gp_func constexpr gp_int3(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) { }
    gp_func gp_int3 operator+(const gp_int3 &r) const { return gp_int3(x + r.x, y + r.y, z + r.z); }
    gp_func gp_int3 &operator+=(const gp_int3 &r) { x += r.x; y += r.y; z += r.z; return *this; }
    gp_func gp_int3 operator-(const gp_int3 &r) const { return gp_int3(x - r.x, y - r.y, z - r.z); }
    gp_func gp_int3 &operator-=(const gp_int3 &r) { x -= r.x; y -= r.y; z -= r.z; return *this; }
    gp_func gp_int3 operator*(const gp_int3 &r) const { return gp_int3(x * r.x, y * r.y, z * r.z); }
    gp_func gp_int3 &operator*=(const gp_int3 &r) { x *= r.x; y *= r.y; z *= r.z; return *this; }
    gp_func gp_int3 operator/(const gp_int3 &r) const { return gp_int3(x / r.x, y / r.y, z / r.z); }
    gp_func gp_int3 &operator/=(const gp_int3 &r) { x /= r.x; y /= r.y; z /= r.z; return *this; }
    gp_func gp_int3 operator*(int32_t r) const { return gp_int3(x * r, y * r, z * r); }
    gp_func gp_int3 &operator*=(int32_t r) { x *= r; y *= r; z *= r; return *this; }
    gp_func gp_int3 operator/(int32_t r) const { return gp_int3(x / r, y / r, z / r); }
    gp_func gp_int3 &operator/=(int32_t r) { x /= r; y /= r; z /= r; return *this; }
};

struct alignas(16) gp_int4 {
    int32_t x, y, z, w;
    gp_func constexpr gp_int4() : x(0), y(0), z(0), w(0) { }
    gp_func constexpr gp_int4(int32_t x, int32_t y, int32_t z, int32_t w) : x(x), y(y), z(z), w(w) { }
    gp_func gp_int4 operator+(const gp_int4 &r) const { return gp_int4(x + r.x, y + r.y, z + r.z, w + r.w); }
    gp_func gp_int4 &operator+=(const gp_int4 &r) { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }
    gp_func gp_int4 operator-(const gp_int4 &r) const { return gp_int4(x - r.x, y - r.y, z - r.z, w - r.w); }
    gp_func gp_int4 &operator-=(const gp_int4 &r) { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }
    gp_func gp_int4 operator*(const gp_int4 &r) const { return gp_int4(x * r.x, y * r.y, z * r.z, w * r.w); }
    gp_func gp_int4 &operator*=(const gp_int4 &r) { x *= r.x; y *= r.y; z *= r.z; w *= r.w; return *this; }
    gp_func gp_int4 operator/(const gp_int4 &r) const { return gp_int4(x / r.x, y / r.y, z / r.z, w / r.w); }
    gp_func gp_int4 &operator/=(const gp_int4 &r) { x /= r.x; y /= r.y; z /= r.z; w /= r.w; return *this; }
    gp_func gp_int4 operator*(int32_t r) const { return gp_int4(x * r, y * r, z * r, w * r); }
    gp_func gp_int4 &operator*=(int32_t r) { x *= r; y *= r; z *= r; w *= r; return *this; }
    gp_func gp_int4 operator/(int32_t r) const { return gp_int4(x / r, y / r, z / r, w / r); }
    gp_func gp_int4 &operator/=(int32_t r) { x /= r; y /= r; z /= r; w /= r; return *this; }
};

struct alignas(8) gp_uint2 {
    uint32_t x, y;
    gp_func constexpr gp_uint2() : x(0), y(0) { }
    gp_func constexpr gp_uint2(uint32_t x, uint32_t y) : x(x), y(y) { }
    gp_func gp_uint2 operator+(const gp_uint2 &r) const { return gp_uint2(x + r.x, y + r.y); }
    gp_func gp_uint2 &operator+=(const gp_uint2 &r) { x += r.x; y += r.y; return *this; }
    gp_func gp_uint2 operator-(const gp_uint2 &r) const { return gp_uint2(x - r.x, y - r.y); }
    gp_func gp_uint2 &operator-=(const gp_uint2 &r) { x -= r.x; y -= r.y; return *this; }
    gp_func gp_uint2 operator*(const gp_uint2 &r) const { return gp_uint2(x * r.x, y * r.y); }
    gp_func gp_uint2 &operator*=(const gp_uint2 &r) { x *= r.x; y *= r.y; return *this; }
    gp_func gp_uint2 operator/(const gp_uint2 &r) const { return gp_uint2(x / r.x, y / r.y); }
    gp_func gp_uint2 &operator/=(const gp_uint2 &r) { x /= r.x; y /= r.y; return *this; }
    gp_func gp_uint2 operator*(uint32_t r) const { return gp_uint2(x * r, y * r); }
    gp_func gp_uint2 &operator*=(uint32_t r) { x *= r; y *= r; return *this; }
    gp_func gp_uint2 operator/(uint32_t r) const { return gp_uint2(x / r, y / r); }
    gp_func gp_uint2 &operator/=(uint32_t r) { x /= r; y /= r; return *this; }
};

struct alignas(16) gp_uint3 {
    uint32_t x, y, z;
    gp_func constexpr gp_uint3() : x(0), y(0), z(0) { }
    gp_func constexpr gp_uint3(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) { }
    gp_func gp_uint3 operator+(const gp_uint3 &r) const { return gp_uint3(x + r.x, y + r.y, z + r.z); }
    gp_func gp_uint3 &operator+=(const gp_uint3 &r) { x += r.x; y += r.y; z += r.z; return *this; }
    gp_func gp_uint3 operator-(const gp_uint3 &r) const { return gp_uint3(x - r.x, y - r.y, z - r.z); }
    gp_func gp_uint3 &operator-=(const gp_uint3 &r) { x -= r.x; y -= r.y; z -= r.z; return *this; }
    gp_func gp_uint3 operator*(const gp_uint3 &r) const { return gp_uint3(x * r.x, y * r.y, z * r.z); }
    gp_func gp_uint3 &operator*=(const gp_uint3 &r) { x *= r.x; y *= r.y; z *= r.z; return *this; }
    gp_func gp_uint3 operator/(const gp_uint3 &r) const { return gp_uint3(x / r.x, y / r.y, z / r.z); }
    gp_func gp_uint3 &operator/=(const gp_uint3 &r) { x /= r.x; y /= r.y; z /= r.z; return *this; }
    gp_func gp_uint3 operator*(uint32_t r) const { return gp_uint3(x * r, y * r, z * r); }
    gp_func gp_uint3 &operator*=(uint32_t r) { x *= r; y *= r; z *= r; return *this; }
    gp_func gp_uint3 operator/(uint32_t r) const { return gp_uint3(x / r, y / r, z / r); }
    gp_func gp_uint3 &operator/=(uint32_t r) { x /= r; y /= r; z /= r; return *this; }
};

struct alignas(16) gp_uint4 {
    uint32_t x, y, z, w;
    gp_func constexpr gp_uint4() : x(0), y(0), z(0), w(0) { }
    gp_func constexpr gp_uint4(uint32_t x, uint32_t y, uint32_t z, uint32_t w) : x(x), y(y), z(z), w(w) { }
    gp_func gp_uint4 operator+(const gp_uint4 &r) const { return gp_uint4(x + r.x, y + r.y, z + r.z, w + r.w); }
    gp_func gp_uint4 &operator+=(const gp_uint4 &r) { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }
    gp_func gp_uint4 operator-(const gp_uint4 &r) const { return gp_uint4(x - r.x, y - r.y, z - r.z, w - r.w); }
    gp_func gp_uint4 &operator-=(const gp_uint4 &r) { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }
    gp_func gp_uint4 operator*(const gp_uint4 &r) const { return gp_uint4(x * r.x, y * r.y, z * r.z, w * r.w); }
    gp_func gp_uint4 &operator*=(const gp_uint4 &r) { x *= r.x; y *= r.y; z *= r.z; w *= r.w; return *this; }
    gp_func gp_uint4 operator/(const gp_uint4 &r) const { return gp_uint4(x / r.x, y / r.y, z / r.z, w / r.w); }
    gp_func gp_uint4 &operator/=(const gp_uint4 &r) { x /= r.x; y /= r.y; z /= r.z; w /= r.w; return *this; }
    gp_func gp_uint4 operator*(uint32_t r) const { return gp_uint4(x * r, y * r, z * r, w * r); }
    gp_func gp_uint4 &operator*=(uint32_t r) { x *= r; y *= r; z *= r; w *= r; return *this; }
    gp_func gp_uint4 operator/(uint32_t r) const { return gp_uint4(x / r, y / r, z / r, w / r); }
    gp_func gp_uint4 &operator/=(uint32_t r) { x /= r; y /= r; z /= r; w /= r; return *this; }
};

static gp_forceinline gp_func gp_uint  gp_cast_uint (const gp_int   &v) { return (gp_uint)v; }
static gp_forceinline gp_func gp_uint2 gp_cast_uint2(const gp_int2  &v) { return gp_uint2((uint32_t)v.x, (uint32_t)v.y); }
static gp_forceinline gp_func gp_uint3 gp_cast_uint3(const gp_int3  &v) { return gp_uint3((uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z); }
static gp_forceinline gp_func gp_uint4 gp_cast_uint4(const gp_int4  &v) { return gp_uint4((uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w); }
static gp_forceinline gp_func gp_int   gp_cast_int  (const gp_uint  &v) { return (gp_int)v; }
static gp_forceinline gp_func gp_int2  gp_cast_int2 (const gp_uint2 &v) { return gp_int2((int32_t)v.x, (int32_t)v.y); }
static gp_forceinline gp_func gp_int3  gp_cast_int3 (const gp_uint3 &v) { return gp_int3((int32_t)v.x, (int32_t)v.y, (int32_t)v.z); }
static gp_forceinline gp_func gp_int4  gp_cast_int4 (const gp_uint4 &v) { return gp_int4((int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w); }

#endif

#if defined(GP_OPENCL_SOURCE) || defined(__OPENCL_VERSION__)

#define int8_t char
#define uint8_t uchar
#define int16_t short
#define uint16_t ushort
#define int32_t int
#define uint32_t uint
#define int64_t long
#define uint64_t ulong

typedef uint gp_atomic_uint;
typedef float gp_float;
typedef float2 gp_float2;
typedef float3 gp_float3;
typedef float4 gp_float4;
typedef uint gp_uint;
typedef uint2 gp_uint2;
typedef uint3 gp_uint3;
typedef uint4 gp_uint4;
typedef int gp_int;
typedef int2 gp_int2;
typedef int3 gp_int3;
typedef int4 gp_int4;

#define gp_float(x) (float)(x)
#define gp_float2(x, y) (float2)(x, y)
#define gp_float3(x, y, z) (float3)(x, y, z)
#define gp_float4(x, y, z, w) (float4)(x, y, z, w)
#define gp_uint(x) (uint)(x)
#define gp_uint2(x, y) (uint2)(x, y)
#define gp_uint3(x, y, z) (uint3)(x, y, z)
#define gp_uint4(x, y, z, w) (uint4)(x, y, z, w)
#define gp_int(x) (int)(x)
#define gp_int2(x, y) (int2)(x, y)
#define gp_int3(x, y, z) (int3)(x, y, z)
#define gp_int4(x, y, z, w) (int4)(x, y, z, w)

#define gp_args

#define gp_kernel_decl(p_name, p_x, p_y, p_z, p_args) \
    __attribute__((reqd_work_group_size(p_x, p_y, p_z))) __kernel void p_name p_args

#define gp_kernel_impl(p_name, p_x, p_y, p_z, p_args) \
    __attribute__((reqd_work_group_size(p_x, p_y, p_z))) __kernel void p_name p_args

#define gp_kernel(p_name, p_x, p_y, p_z, p_args) \
    __kernel void p_name p_args

#define gp_global_dim1 gp_uint
#define gp_global_dim2 gp_uint2
#define gp_global_dim3 gp_uint3

#define gp_const(p_name) p_name
#define gp_buffer(p_name) __global p_name* restrict
#define gp_shared_buffer(p_type) __local p_type * restrict
#define gp_global __global
#define gp_shared __local

#define gp_shared_buffer_init(p_type, p_name, p_buffer) __local p_type * restrict p_name = (__local p_type* restrict)(p_buffer)

#define gp_local_ptr __private

#define gp_tile_size_1d() (uint)(get_local_size(0))
#define gp_tile_size_2d() (uint2)(get_local_size(0), get_local_size(1))
#define gp_tile_size_3d() (uint3)(get_local_size(0), get_local_size(1), get_local_size(2))
#define gp_tile_index_1d() (uint)(get_group_id(0))
#define gp_tile_index_2d() (uint2)(get_group_id(0), get_group_id(1))
#define gp_tile_index_3d() (uint3)(get_group_id(0), get_group_id(1), get_group_id(2))
#define gp_local_index_1d() (uint)(get_local_id(0))
#define gp_local_index_2d() (uint2)(get_local_id(0), get_local_id(1))
#define gp_local_index_3d() (uint3)(get_local_id(0), get_local_id(1), get_local_id(2))
#define gp_global_index_1d() (uint)(get_global_id(0))
#define gp_global_index_2d() (uint2)(get_global_id(0), get_global_id(1))
#define gp_global_index_3d() (uint3)(get_global_id(0), get_global_id(1), get_global_id(2))

#define gp_local_linear_size_1d() (get_local_size(0))
#define gp_local_linear_size_2d() (get_local_size(0) * get_local_size(1))
#define gp_local_linear_size_3d() (get_local_size(0) * get_local_size(1) * get_local_size(2))
#define gp_local_linear_index_1d() (get_local_id(0))
#define gp_local_linear_index_2d() (get_local_id(1)*get_local_size(0) + get_local_id(0))
#define gp_local_linear_index_3d() ((get_local_id(2)*get_local_size(1) + get_local_id(1))*get_local_size(0) + get_local_id(0))

#define gp_local_index_linear() ((gp_tile_size_z>1 ? gp_tile_size_y*gp_z : 0) + (gp_tile_size_y>1 ? gp_tile_size_x*gp_y : 0) + gp_x)

#define gp_shared __local
#define gp_global_constant static __constant

#define gp_for_tile()
#define gp_once_per_tile_1d() if (get_local_id(0) == 0)
#define gp_once_per_tile_2d() if (get_local_id(0) == 0 && get_local_id(1) == 0)
#define gp_once_per_tile_3d() if (get_local_id(0) == 0 && get_local_id(1) == 0 && get_local_id(2) == 0)

#define gp_tile_sync_shared() barrier(CLK_LOCAL_MEM_FENCE)
#define gp_tile_sync_full() barrier(CLK_GLOBAL_MEM_FENCE)

#define gp_forceinline
#define gp_noinline

#define gp_atomic_load(ref) (ref)
#define gp_atomic_store(ref, value) ((ref) = (value))
#define gp_atomic_add(ref, value) atomic_add(&(ref), (value))
#define gp_atomic_or(ref, value) atomic_or(&(ref), (value))
#define gp_atomic_xchg(ref, value) atomic_xchg(&(ref), (value))

#define gp_fabs(a) fabs(a)
#define gp_sqrt(a) sqrt(a)
#define gp_min(a, b) min(a, b)
#define gp_max(a, b) max(a, b)
#define gp_isnan(a) isnan(a)

#define gp_cast_uint(v) convert_uint(v)
#define gp_cast_uint2(v) convert_uint2(v)
#define gp_cast_uint3(v) convert_uint3(v)
#define gp_cast_uint4(v) convert_uint4(v)
#define gp_cast_int(v) convert_int(v)
#define gp_cast_int2(v) convert_int2(v)
#define gp_cast_int3(v) convert_int3(v)
#define gp_cast_int4(v) convert_int4(v)

#define gp_sin(a) sin(a)
#define gp_cos(a) cos(a)

#define gp_alignas(align) __attribute__((aligned(align)))

#elif defined(GP_CUDA_SOURCE) || defined(__CUDACC__)

#include <stdint.h>

struct gp_kernel_info
{
    uint32_t global_size_x;
    uint32_t global_size_y;
    uint32_t global_size_z;
};

typedef uint32_t gp_atomic_uint;

#define gp_args(...) __VA_ARGS__

#define gp_kernel_decl(p_name, p_x, p_y, p_z, p_args) \
    namespace p_name { \
        extern "C" __global__ void p_name(gp_kernel_info gp_info, p_args); \
    }

#define gp_kernel_impl(p_name, p_x, p_y, p_z, p_args) \
    namespace p_name { \
        const constexpr uint32_t gp_tile_size_x = p_x, gp_tile_size_y = p_y, gp_tile_size_z = p_z; \
        extern "C" __global__ void p_name(p_args); \
    } \
    extern "C" __global__ void p_name::p_name(p_args)

#define gp_kernel(p_name, p_x, p_y, p_z, p_args) \
    gp_kernel_impl(p_name, p_x, p_y, p_z, gp_args(p_args))

#define gp_global_dim1 gp_uint
#define gp_global_dim2 gp_uint2
#define gp_global_dim3 gp_uint3

#define gp_const(p_name) p_name
#define gp_buffer(p_name) p_name* __restrict__
#define gp_shared_buffer(p_type) uint32_t
#define gp_global
#define gp_shared

#define gp_shared_buffer_init(p_type, p_name, p_buffer) \
    extern __shared__ int gp_shared_memory[]; \
    p_type *p_name = (p_type*)(gp_shared_memory + p_buffer)

#define gp_local_ptr

#define gp_tile_size_1d() gp_uint(gp_tile_size_x)
#define gp_tile_size_2d() gp_uint2(gp_tile_size_x, gp_tile_size_y)
#define gp_tile_size_3d() gp_uint3(gp_tile_size_x, gp_tile_size_y, gp_tile_size_y)
#define gp_tile_index_1d() (blockIdx.x)
#define gp_tile_index_2d() gp_uint2(blockIdx.x, blockIdx.y)
#define gp_tile_index_3d() gp_uint3(blockIdx.x, blockIdx.y, blockIdx.z)
#define gp_local_index_1d() (threadIdx.x)
#define gp_local_index_2d() gp_uint2(threadIdx.x, threadIdx.y)
#define gp_local_index_3d() gp_uint3(threadIdx.x, threadIdx.y, threadIdx.z)
#define gp_global_index_1d() (blockIdx.x*gp_tile_size_x+threadIdx.x)
#define gp_global_index_2d() gp_uint2(blockIdx.x*gp_tile_size_x+threadIdx.x, blockIdx.y*gp_tile_size_y+threadIdx.y)
#define gp_global_index_3d() gp_uint3(blockIdx.x*gp_tile_size_x+threadIdx.x, blockIdx.y*gp_tile_size_y+threadIdx.y, blockIdx.z*gp_tile_size_z+threadIdx.z)

#define gp_local_linear_size_1d() (gp_tile_size_x)
#define gp_local_linear_size_2d() (gp_tile_size_x * gp_tile_size_y)
#define gp_local_linear_size_3d() (gp_tile_size_x * gp_tile_size_y * gp_tile_size_z)
#define gp_local_linear_index_1d() (threadIdx.x)
#define gp_local_linear_index_2d() (threadIdx.y*gp_tile_size_x + threadIdx.x)
#define gp_local_linear_index_3d() ((threadIdx.z*gp_tile_size_y + threadIdx.y)*gp_tile_size_x + threadIdx.x)

#define gp_shared __shared__
#define gp_global_constant static __device__

#define gp_for_tile()
#define gp_once_per_tile_1d() if (threadIdx.x == 0)
#define gp_once_per_tile_2d() if (threadIdx.x == 0 && threadIdx.y == 0)
#define gp_once_per_tile_3d() if (threadIdx.x == 0 && threadIdx.y == 0 && threadIdx.z == 0)

#define gp_tile_sync_shared() __syncthreads()
#define gp_tile_sync_full() __syncthreads()

#define gp_sin(a) sinf(a)
#define gp_cos(a) cosf(a)

// TOOD
#define gp_atomic_load(ref) (ref)
#define gp_atomic_store(ref, value) ((ref) = (value))
#define gp_atomic_add(ref, value) atomicAdd(&(ref), (value))
#define gp_atomic_or(ref, value) atomicOr(&(ref), (value))
#define gp_atomic_xchg(ref, value) atomicExch(&(ref), (value))

static gp_forceinline gp_func float gp_fabs(float a) { return fabsf(a); }
static gp_forceinline gp_func float gp_sqrt(float a) { return sqrtf(a); }
static gp_forceinline gp_func float gp_min(float a, float b) { return fminf(a, b); }
static gp_forceinline gp_func float gp_max(float a, float b) { return fmaxf(a, b); }
static gp_forceinline gp_func bool gp_isnan(float a) { return isnan(a); }

#elif defined(GP_METAL_SOURCE) || defined(__METAL_VERSION__)

#include <metal_common>
#include <metal_integer>
#include <metal_math>
#include <metal_relational>
#include <metal_atomic>

typedef float gp_float;
typedef float2 gp_float2;
typedef float3 gp_float3;
typedef float4 gp_float4;
typedef uint32_t gp_uint;
typedef uint2 gp_uint2;
typedef uint3 gp_uint3;
typedef uint4 gp_uint4;
typedef int32_t gp_int;
typedef int2 gp_int2;
typedef int3 gp_int3;
typedef int4 gp_int4;

typedef metal::atomic_uint gp_atomic_uint;

#define gp_args(...) __VA_ARGS__

#define gp_kernel_decl(p_name, p_x, p_y, p_z, p_args) \
    namespace p_name { \
        kernel void p_name(gp_uint3, gp_uint3, p_args); \
    }

#define gp_kernel_impl(p_name, p_x, p_y, p_z, p_args) \
    kernel void p_name( \
        gp_uint3 gp_tile_index [[threadgroup_position_in_grid]], \
        gp_uint3 gp_local_index [[thread_position_in_threadgroup]], \
        gp_uint3 gp_tile_size [[threads_per_threadgroup]], \
        p_args)

#define gp_kernel(p_name, p_x, p_y, p_z, p_args) \
    gp_kernel_impl(p_name, p_x, p_y, p_z, gp_args(p_args))

#define gp_global_dim1 constant gp_uint&
#define gp_global_dim2 constant gp_uint2&
#define gp_global_dim3 constant gp_uint3&

#define gp_const(p_name) constant p_name&
#define gp_buffer(p_name) device p_name* __restrict__
#define gp_shared_buffer(p_type) threadgroup p_type*
#define gp_global device
#define gp_shared threadgroup

#define gp_shared_buffer_init(p_type, p_name, p_buffer) \
    threadgroup p_type *p_name = p_buffer

#define gp_local_ptr

#define gp_tile_size_1d() gp_tile_size.x
#define gp_tile_size_2d() gp_tile_size.xy
#define gp_tile_size_3d() gp_tile_size
#define gp_tile_index_1d() gp_tile_index.x
#define gp_tile_index_2d() gp_tile_index.xy
#define gp_tile_index_3d() gp_tile_index
#define gp_local_index_1d() gp_local_index.x
#define gp_local_index_2d() gp_local_index.xy
#define gp_local_index_3d() gp_local_index
#define gp_global_index_1d() (gp_tile_index.x*gp_tile_size.x + gp_local_index.x)
#define gp_global_index_2d() (gp_tile_index.xy*gp_tile_size.xy + gp_local_index.xy)
#define gp_global_index_3d() (gp_tile_index*gp_tile_size + gp_local_index)

#define gp_local_linear_size_1d() (gp_tile_size.x)
#define gp_local_linear_size_2d() (gp_tile_size.x * gp_tile_size.y)
#define gp_local_linear_size_3d() (gp_tile_size.x * gp_tile_size.y * gp_tile_size.z)
#define gp_local_linear_index_1d() (gp_local_index.x)
#define gp_local_linear_index_2d() (gp_local_index.y*gp_tile_size.x + gp_local_index.x)
#define gp_local_linear_index_3d() ((gp_local_index.z*gp_tile_size.y + gp_local_index.y)*gp_tile_size.x + gp_local_index.x)

#define gp_shared threadgroup
#define gp_global_constant static __device__

#define gp_for_tile()
#define gp_once_per_tile_1d() if (gp_local_index.x == 0)
#define gp_once_per_tile_2d() if (gp_local_index.x == 0 && gp_local_index.y == 0)
#define gp_once_per_tile_3d() if (gp_local_index.x == 0 && gp_local_index.y == 0 && gp_local_index.z == 0)

#define gp_tile_sync_shared() threadgroup_barrier(metal::mem_flags::mem_threadgroup)
#define gp_tile_sync_full() threadgroup_barrier(metal::mem_flags::mem_device)

#define gp_sin(a) metal::sin(a)
#define gp_cos(a) metal::cos(a)

#define gp_atomic_load(ref) atomic_load_explicit(&(ref), metal::memory_order_relaxed)
#define gp_atomic_store(ref, value) atomic_store_explicit(&(ref), (value), metal::memory_order_relaxed)
#define gp_atomic_add(ref, value) atomic_fetch_add_explicit(&(ref), (value), metal::memory_order_relaxed)
#define gp_atomic_or(ref, value) atomic_fetch_or_explicit(&(ref), (value), metal::memory_order_relaxed)
#define gp_atomic_xchg(ref, value) atomic_exchange_explicit(&(ref), (value), metal::memory_order_relaxed)

#define gp_fabs(a) metal::abs(a)
#define gp_sqrt(a) metal::sqrt(a)
#define gp_min(a, b) metal::min(a, b)
#define gp_max(a, b) metal::max(a, b)
#define gp_isnan(a) metal::isnan(a)

#else

#include <stdint.h>

#ifndef gp_assert
#include <assert.h>
#define gp_assert(cond) assert(cond)
#endif

namespace gp {

static const constexpr size_t max_args = 64;

struct tile_indices
{
    void *shared_memory;
    gp_uint3 num_tiles;
    gp_uint3 tile_index;
    gp_uint3 tile_offset;
};

struct module_desc;
struct device_desc;
struct buffer_desc;
struct dispatch_desc;
struct dispatch_opts;
struct untyped_buffer;

struct device_info;

namespace imp {

struct device_base;

// Generic reference counted object holder

struct alignas(4) ref_storage {
    union {
        char data[4];
        uint32_t value;
    };
};

struct ref_object {
    ref_storage refcount;

    ref_object();
    ref_object(const ref_object &rhs) = delete;
    ref_object(ref_object &&rhs) = delete;
    ref_object &operator=(const ref_object &rhs) = delete;
    ref_object &operator=(ref_object &&rhs) = delete;
    virtual ~ref_object();
    virtual void destruct_and_deallocate();

    void retain();
    void release();
};

template <typename T> struct ref;
template <typename T> inline void imp_set(ref<T> &ref, T *ptr);
template <typename T> inline T *imp_get(const ref<T> &ref);

template <typename T>
struct ref {
protected:
    T *ptr;
public:
    ref() : ptr(nullptr) { }
    explicit ref(T *t) : ptr(t) { t->retain(); }
    ref(const ref &r) : ptr(r.ptr) { if (r.ptr) r.ptr->retain(); }
    ref(ref &&r) noexcept : ptr(r.ptr) { r.ptr = nullptr; }
    ref &operator=(const ref &r) {
        if (r.ptr) r.ptr->retain();
        if (ptr) r.ptr->release();
        ptr = r.ptr;
        return *this;
    }
    ref &operator=(ref &&r) noexcept {
        gp_assert(&r != this);
        if (ptr) ptr->release();
        ptr = r.ptr;
        r.ptr = nullptr;
        return *this;
    }
    ~ref() { if (ptr) ptr->release(); }

    explicit operator bool() { return ptr != nullptr; }
    bool operator!() { return ptr == nullptr; }

    template <typename U> friend void gp::imp::imp_set(ref<U> &ref, U *ptr);
    template <typename U> friend U *gp::imp::imp_get(const ref<U> &ref);
};

template <typename T>
inline void imp_set(ref<T> &ref, T *ptr)
{
    if (ref.ptr) ref.ptr->release();
    ref.ptr = ptr;
}

template <typename T>
inline T *imp_get(const ref<T> &ref)
{
    return ref.ptr;
}

struct error_base : ref_object
{
    virtual void destruct_and_deallocate();

    const char *device_name;
    ref<error_base> next;
    size_t length;
    const char *message() { return (const char*)(this + 1); }
};

struct buffer_base : ref_object
{
    device_base *device;
    size_t size_bytes;
    void *cpu_data = nullptr;
    bool valid = true;

    struct be_init_info
    {
        bool initial_copied = false;
        bool zeroed = false;
    };

    virtual bool be_init(const buffer_desc &desc, be_init_info &info) = 0;
    virtual bool be_read(void *data, size_t offset_bytes, size_t size_bytes) = 0;
    virtual bool be_write(const void *data, size_t offset_bytes, size_t size_bytes) = 0;
    virtual bool be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes) = 0;

    buffer_base(device_base *device, const buffer_desc &desc);
    virtual ~buffer_base() override;
    bool read(void *data, size_t offset_bytes, size_t size_bytes);
    bool write(const void *data, size_t offset_bytes, size_t size_bytes);
    bool fill(uint8_t value, size_t offset_bytes, size_t size_bytes);
};

struct device_base : ref_object
{
    struct imp_data;
    imp_data *imp;
    bool valid = true;
    size_t shared_memory_size;

    struct be_dispatch_info
    {
        uintptr_t kernel;
        uint32_t shared_memory_bytes;
    };

    virtual const char *be_name() = 0;
    virtual bool be_get_info(device_info &info) = 0;
    virtual bool be_init(const device_desc &desc) = 0;
    virtual bool be_add_module(const module_desc &desc) = 0;
    virtual buffer_base *be_create_buffer(const buffer_desc &desc) = 0;
    virtual uintptr_t be_find_kernel(const char *name) = 0;
    virtual bool be_dispatch(const gp_uint3 &global_size, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts) = 0;
    virtual bool be_finish() = 0;

    void errorf(const char *fmt, ...);
    void warnf(const char *fmt, ...);

    device_base();
    virtual ~device_base() override;
    bool init(const device_desc &desc);
    bool add_module(const module_desc &desc);
    untyped_buffer create_buffer(size_t element_size, size_t count, const void *data);
    untyped_buffer create_buffer(const buffer_desc &desc);
    untyped_buffer create_bad_buffer(const buffer_desc &desc);
    bool dispatch(const dispatch_desc &desc, const dispatch_opts &opts);
    bool dispatch(const gp_uint3 &num_tiles, const dispatch_desc &desc, const dispatch_opts &opts);
    bool finish();
    ref<error_base> peek_errors();
    ref<error_base> pop_errors();
};

struct kernel_imp_base {
};

template <typename Kernel, typename Prototype>
struct kernel_imp { };

}

// -- API

struct global_dim1 {
    uint32_t x;
    global_dim1(uint32_t x) : x(x) { }
    operator uint32_t() const { return x; }
};

struct global_dim2 : gp_uint2 {
    global_dim2(const gp_uint2 &r) : gp_uint2(r) { }
};

struct global_dim3 : gp_uint3 {
    global_dim3(const gp_uint3 &r) : gp_uint3(r) { }
};

enum class module_type : uint32_t
{
    unknown = 0,
    opencl_source = 0x72736c63, // 'clsr'
    cuda_binary   = 0x6e627563, // 'cubn'
    metal_source  = 0x736c746d, // 'mtls'
    metal_binary  = 0x626c746d, // 'mtlb'
};

struct module_desc
{
    module_type type = module_type::unknown;
    const void *data = nullptr;
    size_t size = 0;
    const char *name = nullptr;
    const char *opts = nullptr;
};

struct device_desc
{
    const gp::module_desc *modules = nullptr;
    size_t num_modules = 0;

    size_t max_errors = 128;

    size_t num_threads = 0;

    size_t shared_memory_size = 0x4000; // 16KiB (OpenCL minimum limit)

    bool prefer_spin_wait = false;
    bool use_opencl = true;
    bool use_cuda = true;
    bool use_metal = true;
    bool use_cpu = true;

    void *opencl_device_id = nullptr;
    void *opencl_context = nullptr;
    void *opencl_command_queue = nullptr;

    int cuda_device = -1;
    void *cuda_context = nullptr;
    void *cuda_stream = nullptr;

    void *metal_device = nullptr;
    void *metal_command_queue = nullptr;
};

struct buffer_desc
{
    size_t size_bytes = 0;

    const void *initial_data = nullptr;
    size_t initial_data_bytes = 0;

    bool uninitialized = false;

    void *device_pointer = nullptr;

    const char *error_message = nullptr;
};

enum class arg_type : uint8_t
{
    constant,
    buffer,
    shared_buffer,
};

struct arg_ptr
{
    uintptr_t data[2];
};

using kernel_cpu_func = void(tile_indices &indices, const arg_ptr *args);

struct arg_info
{
    enum constant_flag
    {
        constant_global_dim = 0x1,
    };

    arg_type type;
    uint8_t flags;
    uint32_t size;
};

struct kernel_info
{
    const char *name;
    uint32_t tile_size[3];
    kernel_cpu_func *cpu_func = nullptr;
    size_t num_args = 0;
    arg_info args[max_args];
};

struct temp_dispatch_desc;

struct dispatch_desc
{
    const kernel_info *kernel;
    arg_ptr args[max_args];

    dispatch_desc() : kernel(nullptr) { }
    dispatch_desc(const temp_dispatch_desc &rhs) = delete;
    dispatch_desc(const kernel_info *kernel) : kernel(kernel) { }
    dispatch_desc(const dispatch_desc &rhs) { copy(rhs); }
    dispatch_desc(dispatch_desc &&rhs) noexcept { copy((dispatch_desc&&)rhs); }
    dispatch_desc &operator=(const dispatch_desc &rhs) { copy(rhs); return *this; }
    dispatch_desc &operator=(dispatch_desc &&rhs) noexcept { copy((dispatch_desc&&)rhs); return *this; }

private:
    void copy(const dispatch_desc &rhs) {
        kernel = rhs.kernel;
        if (rhs.kernel) {
            size_t num = rhs.kernel->num_args;
            for (size_t i = 0; i < num; i++) {
                args[i] = rhs.args[i];
            }
        }
    }
};

struct dispatch_opts
{
    static const dispatch_opts defaults;

    size_t max_threads = 0;
    gp_uint3 debug_offset;
    gp_uint3 debug_extent;
};

struct temp_dispatch_desc : dispatch_desc
{
    temp_dispatch_desc(const kernel_info *kernel) : dispatch_desc(kernel) { }
private:
    temp_dispatch_desc(const temp_dispatch_desc &rhs) = default;
    temp_dispatch_desc(temp_dispatch_desc &&rhs) noexcept = default;
    temp_dispatch_desc &operator=(const temp_dispatch_desc &rhs) = default;
    temp_dispatch_desc &operator=(temp_dispatch_desc &&rhs) noexcept = default;

    template <typename Kernel, typename Prototype>
    friend struct ::gp::imp::kernel_imp;
};

struct untyped_buffer : imp::ref<imp::buffer_base>
{
    size_t byte_size() const {
        return ptr->size_bytes;
    }
};

template <typename T>
struct buffer_view;

struct error : imp::ref<imp::error_base>
{
    const char *device_name() const {
        gp_assert(ptr);
        if (!ptr) return nullptr;
        return ptr->device_name;
    }

    const char *message() const {
        gp_assert(ptr);
        if (!ptr) return nullptr;
        return ptr->message();
    }

    size_t message_length() const {
        gp_assert(ptr);
        if (!ptr) return 0;
        return ptr->length;
    }

    error next() const {
        return (const error&)ptr->next;
    }
};

template <typename T>
struct buffer : untyped_buffer
{
    bool valid() const {
        return ptr && ptr->valid;
    }

    size_t size() const {
        gp_assert(ptr);
        if (!ptr) return 0;
        return ptr->size_bytes / sizeof(T);
    }

    bool read(T *data, size_t offset, size_t count) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->read(data, offset * sizeof(T), count * sizeof(T));
    }

    bool write(const T *data, size_t offset, size_t count) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->write(data, offset * sizeof(T), count * sizeof(T));
    }

    bool fill(uint8_t value, size_t offset, size_t count) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->fill(value, offset * sizeof(T), count * sizeof(T));
    }

    bool fill(uint8_t value) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->fill(value, 0, ptr->size_bytes);
    }

    template <typename U>
    buffer<U> cast() const {
        buffer<U> buf;
        if (ptr) ptr->retain();
        imp::imp_set(buf, ptr);
        return buf;
    }

    buffer_view<T> view() const;
};

struct device_info
{
    device_info() { device[0] = '\0'; }

    bool valid = false;
    const char *backend = "";
    char device[256];
};

struct device : imp::ref<imp::device_base>
{
    bool valid() const {
        return ptr && ptr->valid;
    }

    device_info info() const {
        device_info info = { };
        if (!ptr) return info;
        info.backend = ptr->be_name();
        info.valid = ptr->be_get_info(info);
        return info;
    }

    template <typename T>
    buffer<T> create_buffer(size_t count, const T *data=nullptr) const {
        gp_assert(ptr);
        if (!ptr) return { };
        return (buffer<T>&&)ptr->create_buffer(sizeof(T), count, data);
    }

    template <typename T>
    buffer<T> create_buffer(const buffer_desc &desc) const {
        gp_assert(ptr);
        if (!ptr) return { };
        return (buffer<T>&&)ptr->create_buffer(desc);
    }

    bool add_module(const module_desc &desc) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->add_module(desc);
    }

    bool dispatch(const gp_uint3 &num_tiles, const dispatch_desc &desc, const dispatch_opts &opts=dispatch_opts::defaults) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->dispatch(num_tiles, desc, opts);
    }

    bool dispatch(const gp_uint2 &num_tiles, const dispatch_desc &desc, const dispatch_opts &opts=dispatch_opts::defaults) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->dispatch(gp_uint3(num_tiles.x, num_tiles.y, 1), desc, opts);
    }

    bool dispatch(uint32_t num_tiles, const dispatch_desc &desc, const dispatch_opts &opts=dispatch_opts::defaults) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->dispatch(gp_uint3(num_tiles, 1, 1), desc, opts);
    }

    bool dispatch(const dispatch_desc &desc, const dispatch_opts &opts=dispatch_opts::defaults) const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->dispatch(desc, opts);
    }

    bool finish() const {
        gp_assert(ptr);
        if (!ptr) return false;
        return ptr->finish();
    }

    error peek_errors() const {
        gp_assert(ptr);
        if (!ptr) return { };
        return (error&&)ptr->peek_errors();
    }

    error pop_errors() const {
        gp_assert(ptr);
        if (!ptr) return { };
        return (error&&)ptr->pop_errors();
    }
};

struct buffer_view_base {
    imp::buffer_base *ptr;
    void *cpu_data;
    size_t offset_bytes;
    buffer_view_base(imp::buffer_base *ptr, void *cpu_data, size_t offset_bytes)
        : ptr(ptr), cpu_data(cpu_data), offset_bytes(offset_bytes) {
        gp_assert(ptr);
        gp_assert(offset_bytes <= ptr->size_bytes);
    }
};

template <typename T>
struct buffer_view_imp : buffer_view_base {
    explicit buffer_view_imp(imp::buffer_base *ptr, size_t offset_bytes)
        : buffer_view_base(ptr, ptr && ptr->cpu_data ? ((char*)ptr->cpu_data + offset_bytes) : nullptr, offset_bytes) { }

    template <typename U>
    buffer_view<U> cast() const {
        return (buffer_view<U>&&)(buffer_view_imp&&)buffer_view_imp(ptr, offset_bytes);
    }

    buffer_view<T> offset(size_t offset) const {
        return (buffer_view<T>&&)(buffer_view_imp&&)buffer_view_imp(ptr, offset_bytes + offset * sizeof(T));
    }

    gp_forceinline T &operator[](size_t index) const {
        gp_assert(index * sizeof(T) < ptr->size_bytes - offset_bytes);
        return ((T*)cpu_data)[index];
    }

    gp_forceinline T *operator->() const {
        return (T*)cpu_data;
    }
};

template <typename T>
struct buffer_view : buffer_view_imp<T> {
    using imp_type = buffer_view_imp<T>;
    explicit buffer_view(imp::buffer_base *ptr, size_t offset_bytes) : imp_type(ptr, offset_bytes) { }
    buffer_view(const buffer<T> &buf) : imp_type(imp::imp_get(buf), 0) { }
    buffer_view(const buffer<T> &buf, size_t offset) : imp_type(imp::imp_get(buf), sizeof(T) * offset) { }
};

template <typename T>
struct buffer_view<const T> : buffer_view_imp<const T> {
    using imp_type = buffer_view_imp<const T>;
    explicit buffer_view(imp::buffer_base *ptr, size_t offset_bytes) : imp_type(ptr, offset_bytes) { }
    buffer_view(const buffer<T> &buf) : imp_type(imp::imp_get(buf), 0) { }
    buffer_view(const buffer<T> &buf, size_t offset) : imp_type(imp::imp_get(buf), sizeof(T) * offset) { }
    buffer_view(const buffer<const T> &buf) : imp_type(imp::imp_get(buf), 0) { }
    buffer_view(const buffer<const T> &buf, size_t offset) : imp_type(imp::imp_get(buf), sizeof(T) * offset) { }
    buffer_view(const buffer_view<T> &view) : imp_type(view.ptr, view.offset_bytes) { }
};

template <typename T>
gp_forceinline buffer_view<T> buffer<T>::view() const {
    return buffer_view<T>(*this);
}


struct shared_buffer_base {
    uint32_t size, offset_or_align;
    explicit shared_buffer_base(uint32_t size, uint32_t offset_or_align) : size(size), offset_or_align(offset_or_align) { }
};

template <typename T>
struct shared_buffer : shared_buffer_base {
    explicit shared_buffer(uint32_t count) : shared_buffer_base(count * sizeof(T), alignof(T)) { }
};

template <typename T>
struct shared_buffer_view {
    T *cpu_data;
    size_t size;

    gp_forceinline T &operator[](size_t index) const {
        gp_assert((index + 1) * sizeof(T) <= size);
        return ((T*)cpu_data)[index];
    }

    gp_forceinline T *operator->() const {
        return (T*)cpu_data;
    }
};

device create_device(const device_desc &desc = device_desc{});

namespace imp {

template <typename T>
struct bad_argument_type;

template <typename T>
struct arg_constant_flags { enum { flags = 0 }; };

template <> struct arg_constant_flags<global_dim1> { enum { flags = arg_info::constant_global_dim }; };
template <> struct arg_constant_flags<global_dim2> { enum { flags = arg_info::constant_global_dim }; };
template <> struct arg_constant_flags<global_dim3> { enum { flags = arg_info::constant_global_dim }; };

template <typename T>
struct arg_traits : bad_argument_type<T> {
};

template <typename T> struct arg_traits<const T& gp_template_restrict> {
    static const constexpr arg_info info = { arg_type::constant, arg_constant_flags<T>::flags, sizeof(T) };
    static gp_forceinline arg_ptr to_arg(const T &gp_restrict t) { return { (uintptr_t)&t }; }
    static gp_forceinline const T &gp_restrict from_arg(arg_ptr arg) { return *(const T*)arg.data[0]; }
};

template <typename T> struct arg_traits<buffer_view<T>> {
    static const constexpr arg_info info = { arg_type::buffer, 0, sizeof(T) };
    static gp_forceinline arg_ptr to_arg(buffer_view<T> t) { return { (uintptr_t)t.ptr, t.offset_bytes }; }
    static gp_forceinline buffer_view<T> from_arg(arg_ptr arg) {
        return buffer_view<T>((buffer_base*)arg.data[0], (size_t)arg.data[1]);
    }
};

template <typename T> struct arg_traits<shared_buffer<T>> {
    static const constexpr arg_info info = { arg_type::shared_buffer, 0, sizeof(T) };
    static gp_forceinline arg_ptr to_arg(shared_buffer<T> t) { return { t.size, t.offset_or_align }; }
    static gp_forceinline shared_buffer<T> from_arg(arg_ptr arg) {
        const shared_buffer_base base((uint32_t)arg.data[0], (uint32_t)arg.data[1]);
        return static_cast<const shared_buffer<T>&>(base);
    }
};

template <size_t... N> struct index_seq { };
template <size_t N, size_t... Ns> struct index_seq_init {
    using type = typename index_seq_init<N-1, N-1, Ns...>::type;
};
template <size_t... Ns> struct index_seq_init<0, Ns...> {
    using type = index_seq<Ns...>;
};

template <size_t N, typename T, typename... Ts> struct type_at {
    using type = typename type_at<N - 1, Ts...>::type;
};
template <typename T, typename... Ts> struct type_at<0, T, Ts...> {
    using type = T;
};

template <typename Kernel, typename... Args>
struct kernel_cpu_imp {

    template <size_t N>
    struct arg_at {
        using type = typename type_at<N, Args...>::type;
        static type get(const arg_ptr *args) {
            return arg_traits<type>::from_arg(args[N]);
        }
    };

    template <typename T>
    struct cpu_func_for { };

    template <size_t... N>
    struct cpu_func_for<index_seq<N...>> {
        static void func(tile_indices &gp_indices, const arg_ptr *args) {
            Kernel::cpu_process_tile(gp_indices, arg_at<N>::get(args)...);
        }
    };

    using cpu_func = cpu_func_for<typename index_seq_init<sizeof...(Args)>::type>;
};

template <typename Kernel, typename... Args>
struct kernel_imp<Kernel, void(Args...)> : kernel_imp_base {

    static const ::gp::kernel_info info;

    static ::gp::temp_dispatch_desc create_dispatch(Args... args)
    {
        ::gp::temp_dispatch_desc desc{&info};
        arg_ptr ptrs[] = { arg_traits<Args>::to_arg(args)... };
        for (size_t i = 0; i < sizeof...(Args); i++) {
            desc.args[i] = ptrs[i];
        }
        return desc;
    }
};

template <typename Kernel, typename... Args>
const ::gp::kernel_info kernel_imp<Kernel, void(Args...)>::info = {
    Kernel::name,
    { Kernel::gp_tile_size_x, Kernel::gp_tile_size_y, Kernel::gp_tile_size_z },
    &kernel_cpu_imp<Kernel, Args...>::cpu_func::func,
    sizeof...(Args),
    { arg_traits<Args>::info... },
};

#define gp_imp_kernel_do_decl(p_line, p_name, p_x, p_y, p_z, p_args) \
    namespace gp_imp { using namespace gp; \
        template <typename> static void unused_##p_name##p_line(::gp::tile_indices &gp_indices, p_args); \
    } \
    extern ::gp::temp_dispatch_desc (*const p_name)(p_args); \
    template <typename> static void gp_imp::unused_##p_name##p_line(::gp::tile_indices &gp_indices, p_args)

#define gp_imp_kernel_do_impl(p_line, p_name, p_x, p_y, p_z, p_args) \
    namespace gp_imp { using namespace gp; \
        struct p_name##_kernel : ::gp::imp::kernel_imp<p_name##_kernel, void(p_args)> { \
            static constexpr const char *const name = #p_name; \
            static constexpr const uint32_t gp_tile_size_x = p_x; \
            static constexpr const uint32_t gp_tile_size_y = p_y; \
            static constexpr const uint32_t gp_tile_size_z = p_z; \
            static gp_noinline void cpu_process_tile(::gp::tile_indices &gp_indices, p_args); \
        }; \
    } \
    extern ::gp::temp_dispatch_desc (*const p_name)(p_args); \
    ::gp::temp_dispatch_desc (*const p_name)(p_args) = &gp_imp::p_name##_kernel::create_dispatch; \
    gp_noinline void gp_imp::p_name##_kernel::cpu_process_tile(::gp::tile_indices &gp_indices, p_args)

#define gp_imp_kernel_GP_KERNEL_IMPL(p_line, p_name, p_x, p_y, p_z, p_args) \
    gp_imp_kernel_do_decl(p_line, p_name, p_x, p_y, p_z, gp_args(p_args))

#define gp_imp_kernel_(p_line, p_name, p_x, p_y, p_z, p_args) \
    gp_imp_kernel_do_impl(p_line, p_name, p_x, p_y, p_z, gp_args(p_args))

#define gp_kernel_select2(p_type, p_name, p_x, p_y, p_z, p_args) \
    gp_imp_kernel_##p_type(__LINE__, p_name, p_x, p_y, p_z, gp_args(p_args))

#define gp_kernel_select1(p_type, p_name, p_x, p_y, p_z, p_args) \
    gp_kernel_select2(p_type, p_name, p_x, p_y, p_z, gp_args(p_args))
}

}

typedef uint32_t gp_atomic_uint;

// TODO
#define gp_atomic_load(ref) (ref)
#define gp_atomic_store(ref, value) ((ref) = (value))

uint32_t gp_atomic_add(uint32_t &ref, uint32_t value);
static gp_forceinline uint32_t gp_atomic_add_shared(uint32_t &ref, uint32_t value) {
    uint32_t p = ref; p += value; return p;
}

uint32_t gp_atomic_or(uint32_t &ref, uint32_t value);
static gp_forceinline uint32_t gp_atomic_or_shared(uint32_t &ref, uint32_t value) {
    uint32_t p = ref; p |= value; return p;
}

uint32_t gp_atomic_xchg(uint32_t &ref, uint32_t value);
static gp_forceinline uint32_t gp_atomic_xchg_shared(uint32_t &ref, uint32_t value) {
    uint32_t p = ref; p = value; return p;
}

#define gp_tile_size_1d() gp_uint(gp_tile_size_x)
#define gp_tile_size_2d() gp_uint2(gp_tile_size_x, gp_tile_size_y)
#define gp_tile_size_3d() gp_uint3(gp_tile_size_x, gp_tile_size_y, gp_tile_size_y)
#define gp_tile_index_1d() (gp_indices.tile_index.x)
#define gp_tile_index_2d() gp_uint2(gp_indices.tile_index.x, gp_indices.tile_index.y)
#define gp_tile_index_3d() gp_uint3(gp_indices.tile_index.x, gp_indices.tile_index.y, gp_indices.tile_index.z)
#define gp_local_index_1d() (gp_x)
#define gp_local_index_2d() gp_uint2(gp_x, gp_y)
#define gp_local_index_3d() gp_uint3(gp_x, gp_y, gp_z)
#define gp_global_index_1d() (gp_indices.tile_offset.x+gp_x)
#define gp_global_index_2d() gp_uint2(gp_indices.tile_offset.x+gp_x, gp_indices.tile_offset.y+gp_y)
#define gp_global_index_3d() gp_uint3(gp_indices.tile_offset.x+gp_x, gp_indices.tile_offset.y+gp_y, gp_indices.tile_offset.z+gp_z)

#define gp_local_linear_size_1d() (gp_tile_size_x)
#define gp_local_linear_size_2d() (gp_tile_size_x * gp_tile_size_y)
#define gp_local_linear_size_3d() (gp_tile_size_x * gp_tile_size_y * gp_tile_size_z)
#define gp_local_linear_index_1d() (gp_x)
#define gp_local_linear_index_2d() (gp_y*gp_tile_size_x + gp_x)
#define gp_local_linear_index_3d() ((gp_z*gp_tile_size_y + gp_y)*gp_tile_size_x + gp_x)

#define gp_shared
#define gp_global_constant static

#define gp_global_dim1 const ::gp::global_dim1 & gp_restrict
#define gp_global_dim2 const ::gp::global_dim2 & gp_restrict
#define gp_global_dim3 const ::gp::global_dim3 & gp_restrict
#define gp_const(p_type) const p_type & gp_restrict
#define gp_buffer(p_type) ::gp::buffer_view<p_type>
#define gp_shared_buffer(p_type) ::gp::shared_buffer<p_type>
#define gp_global
#define gp_shared

#define gp_shared_buffer_init(p_type, p_name, p_buffer) ::gp::shared_buffer_view<p_type> p_name { \
    (p_type*)((char*)gp_indices.shared_memory + (p_buffer).offset_or_align), (p_buffer).size }

#define gp_local_ptr

#define gp_local_def(p_type, p_name) p_type p_name##_storage[gp_tile_size_z][gp_tile_size_y][gp_tile_size_x]
#define gp_local_ref(p_name) auto &p_name = p_name##_storage[gp_z][gp_y][gp_x];

#define gp_args(...) __VA_ARGS__

#define gp_kernel_decl(p_name, p_args) \
    gp_imp_kernel_GP_KERNEL_IMPL(__LINE__, p_name, gp_args(p_args))

#define gp_kernel_impl(p_name, p_args) \
    gp_imp_kernel_(__LINE__, p_name, gp_args(p_args))

#define gp_kernel(p_name, p_x, p_y, p_z, p_args) \
    gp_kernel_select1(GP_KERNEL_IMPL, p_name, p_x, p_y, p_z, gp_args(p_args))

#define gp_for_tile() \
    for (uint32_t gp_z = 0; gp_z != gp_tile_size_z; gp_z++) \
    for (uint32_t gp_y = 0; gp_y != gp_tile_size_y; gp_y++) \
    for (uint32_t gp_x = 0; gp_x != gp_tile_size_x; gp_x++) 

#define gp_once_per_tile_1d()
#define gp_once_per_tile_2d()
#define gp_once_per_tile_3d()

#define gp_tile_sync_shared() (void)0
#define gp_tile_sync_full() (void)0

#define gp_sin(a) sinf(a)
#define gp_cos(a) cosf(a)

#define gp_alignas(align) alignas(align)

#ifdef GP_USE_SSE
    static gp_forceinline float gp_fabs(float a) { return _mm_cvtss_f32(_mm_andnot_ps(_mm_set_ss(-0.0f), _mm_set_ss(a))); }
    static gp_forceinline float gp_sqrt(float a) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(a))); }
    static gp_forceinline float gp_min(float a, float b) { return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b))); }
    static gp_forceinline float gp_max(float a, float b) { return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b))); }
    static gp_forceinline bool gp_isnan(float a) { return !_mm_comieq_ss(_mm_set_ss(a), _mm_set_ss(a)); }
#else
    #error "TODO"
#endif

#endif

static gp_func gp_forceinline bool gp_all_less_1d(gp_uint a, gp_uint b) { return a < b; }
static gp_func gp_forceinline bool gp_all_less_2d(gp_uint2 a, gp_uint2 b) { return a.x < b.x && a.y < b.y; }
static gp_func gp_forceinline bool gp_all_less_3d(gp_uint3 a, gp_uint3 b) { return a.x < b.x && a.y < b.y && a.z < b.z; }
static gp_func gp_forceinline bool gp_all_less_4d(gp_uint4 a, gp_uint4 b) { return a.x < b.x && a.y < b.y && a.z < b.z && a.w < b.w; }

static gp_func gp_forceinline gp_float3 gp_float4_xyz(gp_float4 v) { return gp_float3(v.x, v.y, v.z); }

#define gp_for_tile_in_bounds_1d(p_bounds) gp_for_tile() if (gp_all_less_1d(gp_global_index_1d(), (p_bounds)))
#define gp_for_tile_in_bounds_2d(p_bounds) gp_for_tile() if (gp_all_less_2d(gp_global_index_2d(), (p_bounds)))
#define gp_for_tile_in_bounds_3d(p_bounds) gp_for_tile() if (gp_all_less_3d(gp_global_index_3d(), (p_bounds)))

#define gp_for_local_linear_1d(p_type, p_name, p_bounds) for (p_type p_name = (p_type)gp_local_linear_index_1d(); p_name < p_bounds; p_name += (p_type)gp_local_linear_size_1d())
#define gp_for_local_linear_2d(p_type, p_name, p_bounds) for (p_type p_name = (p_type)gp_local_linear_index_2d(); p_name < p_bounds; p_name += (p_type)gp_local_linear_size_2d())
#define gp_for_local_linear_3d(p_type, p_name, p_bounds) for (p_type p_name = (p_type)gp_local_linear_index_3d(); p_name < p_bounds; p_name += (p_type)gp_local_linear_size_3d())

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

#endif

#ifdef GP_IMPLEMENTATION
#ifndef GP_IMPLEMENTED
#define GP_IMPLEMENTED

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>

#ifndef GP_NO_CPU
    #include <thread>

    #if !defined(GP_NO_CPUID)
        #if defined(_MSC_VER) && defined(_M_X64)
            #include <intrin.h>
            #define GP_HAS_X64_CPUID
            static void gp_x64_cpuid(char *dst, int leaf) {
                __cpuid((int*)dst, leaf);
            }
        #elif (defined(__GNUC__) || defined(__clang__)) && defined(__x86_64__)
            #include <cpuid.h>
            #define GP_HAS_X64_CPUID
            static void gp_x64_cpuid(char *dst, int leaf) {
                int eax, ebx, ecx, edx;
                __cpuid(leaf, eax, ebx, ecx, edx);
                memcpy(dst +  0, &eax, 4);
                memcpy(dst +  4, &ebx, 4);
                memcpy(dst +  8, &ecx, 4);
                memcpy(dst + 12, &edx, 4);
            }
        #endif
    #endif

    #if defined(GP_HAS_X64_CPUID)
        static char *gp_get_cpu_name(char *dst, size_t length) {
            gp_assert(length >= 3*16 + 1);
            for (int i = 2; i <= 4; i++) {
                gp_x64_cpuid(dst, 0x80000000 + i);
                dst += 16;
            }
            return dst;
        }
    #else
        static void gp_get_cpu_name(char *dst, size_t length) { return dst; }
    #endif
#endif

#ifdef GP_USE_OPENCL
    #if defined(__APPLE__)
        #include <OpenCL/cl.h>
    #else
        #include <CL/cl.h>
    #endif
#endif

#ifdef GP_USE_CUDA
    #include <cuda.h>
#endif

#ifdef GP_USE_METAL
    #include <Foundation/Foundation.h>
    #include <Metal/Metal.h>
#endif

#ifdef _WIN32
    extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *message);
#endif

extern void dof_log(const char *fmt, ...);

namespace gp {
namespace imp {

// -- Utility

using mutex = std::mutex;
using mutex_guard = std::lock_guard<std::mutex>;

static constexpr const double bad_score = -1e20;

double at_most(double a, double b) { return a < b ? a : b; }

void debug_print(const char *str)
{
    fprintf(stderr, "%s", str);
#ifdef _WIN32
    OutputDebugStringA(str);
#endif
}

struct kernel_cache
{
    struct entry_type
    {
        uintptr_t kernel = 0;
        uint32_t hash = 0;
        uint32_t length = 0;
        std::unique_ptr<char[]> data;
    };

    std::unique_ptr<entry_type[]> entries;
    size_t capacity = 0, size = 0;

    gp_noinline void rehash()
    {
        size_t cap = capacity ? capacity * 2 : 32;
        std::unique_ptr<entry_type[]> new_entries { new entry_type[cap] };
        for (size_t i = 0; i < capacity; i++) {
            uint32_t ix = entries[i].hash;
            while (new_entries[ix & (cap - 1)].kernel) ix++;
            new_entries[ix & (cap - 1)] = std::move(entries[i]);
        }
        std::swap(entries, new_entries);
        capacity = cap;
    }

    uintptr_t &resolve(const char *name)
    {
        if (size == capacity) rehash();
        size_t mask = capacity - 1;

        uint32_t length = 0;
        uint32_t hash = 0x811c9dc5;
        for (const char *p = name; *p; p++) {
            hash = (hash ^ (uint8_t)*p) * 0x01000193;
            length++;
        }

        uint32_t ix = hash & mask;
        entry_type *entry_ptr = entries.get();
        while (entry_ptr[ix].kernel) {
            if (entry_ptr[ix].hash == hash && entry_ptr[ix].length == length
                    && !memcmp(name, entry_ptr[ix].data.get(), length)) {
                return entry_ptr[ix].kernel;
            }
            ix = (ix + 1) & mask;
        }

        entry_ptr[ix].hash = hash;
        entry_ptr[ix].length = length;
        entry_ptr[ix].data.reset(new char[length + 1]);
        memcpy(entry_ptr[ix].data.get(), name, length + 1);
        size++;
        return entry_ptr[ix].kernel;
    }
};


// -- Reference counted objects

using refcount_t = std::atomic_uint32_t;
static_assert(sizeof(refcount_t) <= sizeof(ref_storage), "Refcount size");
static_assert(alignof(refcount_t) <= alignof(ref_storage), "Refcount alignment");

inline refcount_t &refc(ref_storage &s) { return (refcount_t&)s.data; }

ref_object::ref_object()
{
    new (&refc(refcount)) refcount_t(1);
}

ref_object::~ref_object()
{
    refc(refcount).~refcount_t();
}

void ref_object::retain()
{
    refc(refcount).fetch_add(1u, std::memory_order_acquire);
}

void ref_object::release()
{
    if (refc(refcount).fetch_sub(1u, std::memory_order_release) == 1u) {
        std::atomic_thread_fence(std::memory_order_acquire);
        destruct_and_deallocate();
    }
}

void ref_object::destruct_and_deallocate()
{
    delete this;
}

// -- Bad resources

struct bad_device : device_base
{
    void fail_use(const char *reason) {
        errorf("Trying to %s a bad device", reason);
    }

    bad_device() : device_base() { valid = false; }

    virtual const char *be_name() override { return "bad"; }
    virtual bool be_get_info(device_info&) override { fail_use("get info"); return false; }
    virtual bool be_init(const device_desc &desc) override { fail_use("initialize"); return false; }
    virtual bool be_add_module(const module_desc &desc) override { fail_use("add module to"); return false; }
    virtual buffer_base *be_create_buffer(const buffer_desc &desc) override;
    virtual uintptr_t be_find_kernel(const char *name) override { fail_use("use a kernel from"); return false; }
    virtual bool be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts) override { fail_use("dispatch using"); return false; }
    virtual bool be_finish() override { fail_use("finish operations on"); return false; }
};

struct bad_buffer : buffer_base
{
    void fail_use(const char *reason) {
        device->errorf("Trying to %s a bad buffer", reason);
    }

    bad_buffer(device_base *device, const buffer_desc &desc) : buffer_base(device, desc) { valid = false; }

    virtual bool be_init(const buffer_desc &desc, be_init_info &info) override { fail_use("initialize"); return false; }
    virtual bool be_read(void *data, size_t offset_bytes, size_t size_bytes) override { fail_use("read from"); return false; }
    virtual bool be_write(const void *data, size_t offset_bytes, size_t size_bytes) override { fail_use("write to"); return false; }
    virtual bool be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes) override { fail_use("fill"); return false; }
};

buffer_base *bad_device::be_create_buffer(const buffer_desc &desc)
{
    fail_use("create a buffer from");
    return new bad_buffer(this, desc);
}

// -- Base functionality

error_base *make_error(const char *device_name, const char *fmt, va_list args)
{
    va_list args2;
    va_copy(args2, args);

    error_base *err = nullptr;

    int int_length = vsnprintf(nullptr, 0, fmt, args);
    if (int_length >= 0) {
        size_t length = (size_t)int_length;
        err = (error_base*)malloc(sizeof(error_base) + length + 1);
        if (err) {
            new (err) error_base();
            err->length = (size_t)length;
            vsnprintf((char*)(err + 1), length + 1, fmt, args2);
        }
    }

    if (!err) {
        err = (error_base*)malloc(sizeof(error_base) + 1);
        if (err) {
            new (err) error_base();
            err->length = 0;
            *(char*)(err + 1) = '\0';
        }
    }

    if (err) {
        err->device_name = device_name;
    }

    va_end(args2);

    return err;
}

void error_base::destruct_and_deallocate()
{
    error_base *self = this;
    self->~error_base();
    free(self);
}

struct device_base::imp_data
{
    uint32_t module_counter = 0;
    std::mutex mutex;
    kernel_cache kern_cache;

    std::mutex error_mutex;
    size_t max_errors = 1;
    size_t error_count = 0;
    ref<error_base> error_head;
    ref<error_base> error_tail;
};

buffer_base::buffer_base(device_base *device, const buffer_desc &desc)
    : device(device)
    , size_bytes(desc.size_bytes)
{
    gp_assert(device);
    device->retain();
}

buffer_base::~buffer_base()
{
    device->release();
}

bool buffer_base::read(void *data, size_t offset_bytes, size_t size_bytes)
{
    if (offset_bytes > this->size_bytes || size_bytes > this->size_bytes - offset_bytes) {
        device->errorf("buffer read(size=%zu, offset=%zu) out of bounds (buffer is %zu bytes)",
            size_bytes, offset_bytes, this->size_bytes);
        return false;
    }

    return be_read(data, offset_bytes, size_bytes);
}

bool buffer_base::write(const void *data, size_t offset_bytes, size_t size_bytes)
{
    if (offset_bytes > this->size_bytes || size_bytes > this->size_bytes - offset_bytes) {
        device->errorf("buffer write(size=%zu, offset=%zu) out of bounds (buffer is %zu bytes)",
            size_bytes, offset_bytes, this->size_bytes);
        return false;
    }

    return be_write(data, offset_bytes, size_bytes);
}

bool buffer_base::fill(uint8_t value, size_t offset_bytes, size_t size_bytes)
{
    if (offset_bytes > this->size_bytes || size_bytes > this->size_bytes - offset_bytes) {
        device->errorf("buffer fill(size=%zu, offset=%zu) out of bounds (buffer is %zu bytes)",
            size_bytes, offset_bytes, this->size_bytes);
        return false;
    }

    return be_fill(value, offset_bytes, size_bytes);
}

void device_base::errorf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    error_base *err = make_error(be_name(), fmt, args);
    va_end(args);

    if (err) {
        debug_print("gp/");
        debug_print(be_name());
        debug_print(" error: ");
        debug_print(err->message());
        debug_print("\n");

        mutex_guard mg(imp->error_mutex);
        if (imp->error_count < imp->max_errors) {
            if (imp->error_tail) {
                imp_set(imp_get(imp->error_tail)->next, err);
                imp_set(imp->error_tail, err);
                err->retain();
            } else {
                imp_set(imp->error_tail, err);
                imp->error_head = imp->error_tail;
            }
            imp->error_count++;
        } else {
            err->release();
        }
    }
}

void device_base::warnf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    error_base *err = make_error(be_name(), fmt, args);
    va_end(args);

    if (err) {
        debug_print("gp/");
        debug_print(be_name());
        debug_print(" warning: ");
        debug_print(err->message());
        debug_print("\n");
        err->release();
    }
}

device_base::device_base()
    : imp(new imp_data())
{
}

device_base::~device_base()
{
    delete imp;
}

bool device_base::init(const device_desc &desc)
{
    imp->max_errors = desc.max_errors;
    shared_memory_size = desc.shared_memory_size;

    if (!be_init(desc)) {
        return false;
    }

    for (size_t i = 0; i < desc.num_modules; i++) {
        if (!add_module(desc.modules[i])) return false;
    }

    return true;
}

bool device_base::add_module(const module_desc &desc)
{
    if (desc.size > 0 && !desc.data) {
        errorf("Non-empty module data with null pointer");
        return false;
    }

    mutex_guard mg { imp->mutex };

    module_desc copy = desc;
    uint32_t index = imp->module_counter++;

    char name_buf[128];
    if (!copy.name) {
        snprintf(name_buf, sizeof(name_buf), "modules[%u]", index);
        copy.name = name_buf;
    }

    if (!copy.opts) {
        copy.opts = "";
    }

    if (!be_add_module(copy)) return false;

    return true;
}

untyped_buffer device_base::create_buffer(size_t element_size, size_t count, const void *data)
{
    buffer_desc desc;

    if (element_size == 0) {
        errorf("Trying to create a buffer with empty element size");
        return create_bad_buffer(desc);
    }

    if (SIZE_MAX / element_size < count) {
        errorf("Buffer size %zux%zu overflows", count, element_size);
        return create_bad_buffer(desc);
    }

    desc.size_bytes = count * element_size;
    if (data) {
        desc.initial_data = data;
        desc.initial_data_bytes = element_size * count;
    }

    return create_buffer(desc);
}

untyped_buffer device_base::create_buffer(const buffer_desc &desc)
{
    untyped_buffer buf;

    if (desc.error_message) {
        errorf(desc.error_message);
        return create_bad_buffer(desc);
    }

    if (desc.initial_data_bytes > 0 && !desc.initial_data) {
        errorf("Non-empty initial data with null pointer");
        return create_bad_buffer(desc);
    }

    if (desc.initial_data_bytes > desc.size_bytes) {
        errorf("Trying to write %zu initial bytes to %zu byte buffer");
        return create_bad_buffer(desc);
    }

    buffer_base *base = be_create_buffer(desc);
    if (!base) return create_bad_buffer(desc);
    imp_set(buf, base);

    buffer_base::be_init_info init_info;
    if (!base->be_init(desc, init_info)) return create_bad_buffer(desc);

    // Copy the initial data to the front of the buffer if the backend didn't already
    if (desc.initial_data_bytes > 0 && !init_info.initial_copied) {
        if (!base->be_write(desc.initial_data, 0, desc.initial_data_bytes)) return create_bad_buffer(desc);
    }

    // Zero the rest of the buffer if neccessary and the backend didn't already
    size_t to_zero = desc.size_bytes - desc.initial_data_bytes;
    if (to_zero > 0 && !init_info.zeroed && !desc.uninitialized) {
        if (!base->be_fill(0, desc.initial_data_bytes, to_zero)) return create_bad_buffer(desc);
    }

    return buf;
}

untyped_buffer device_base::create_bad_buffer(const buffer_desc &desc)
{
    untyped_buffer buf;
    buffer_base *base = new bad_buffer(this, desc);
    imp_set(buf, base);
    return buf;
}

bool device_base::dispatch(const dispatch_desc &desc, const dispatch_opts &opts)
{
    gp_uint3 num_tiles;
    bool found_tiles = false;

    for (size_t i = 0; i < desc.kernel->num_args; i++) {
        const arg_info &info = desc.kernel->args[i];

        if (info.type == arg_type::constant && info.flags & arg_info::constant_global_dim) {
            const void *arg = (const void*)desc.args[i].data[0];
            uint32_t x = 1, y = 1, z = 1;
            if (info.size == sizeof(global_dim1)) {
                const global_dim1 *dim = (const global_dim1*)arg;
                x = dim->x;
            } else if (info.size == sizeof(global_dim2)) {
                const global_dim2 *dim = (const global_dim2*)arg;
                x = dim->x; y = dim->y;
            } else if (info.size == sizeof(global_dim3)) {
                const global_dim3 *dim = (const global_dim3*)arg;
                x = dim->x; y = dim->y; z = dim->z;
            }

            num_tiles.x = (x + desc.kernel->tile_size[0] - 1) / desc.kernel->tile_size[0];
            num_tiles.y = (y + desc.kernel->tile_size[1] - 1) / desc.kernel->tile_size[1];
            num_tiles.z = (z + desc.kernel->tile_size[2] - 1) / desc.kernel->tile_size[2];

            if (found_tiles) {
                errorf("%s: Multiple tile dimension arguments", desc.kernel->name);
                return false;
            }
            found_tiles = true;
        }
    }

    if (!found_tiles) {
        errorf("%s: Could not find implicit dispatch size from arguments", desc.kernel->name);
        return false;
    }

    if (!dispatch(num_tiles, desc, opts)) return false;

    return true;
}

bool device_base::dispatch(const gp_uint3 &num_tiles, const dispatch_desc &desc, const dispatch_opts &opts)
{
    mutex_guard mg(imp->mutex);

    const buffer_base *buffers[max_args];
    size_t num_buffers = 0;

    dispatch_desc copy;
    copy.kernel = desc.kernel;

    uint32_t shared_size = 0;

    for (size_t i = 0; i < desc.kernel->num_args; i++) {
        const arg_info &info = desc.kernel->args[i];
        arg_ptr arg = desc.args[i];

        if (info.type == arg_type::constant) {
            copy.args[i] = arg;
        } else if (info.type == arg_type::buffer) {
            const buffer_base *buf = (buffer_base*)arg.data[0];
            if (!buf) {
                errorf("%s: Buffer argument %zu is null", desc.kernel->name, i);
                return false;
            }
            if (!buf->valid) {
                errorf("%s: Buffer argument %zu is not valid", desc.kernel->name, i);
                return false;
            }

            for (size_t i = 0; i < num_buffers; i++) {
                if (buffers[i] == buf) {
                    errorf("%s: Buffer argument %zu already passed, buffers must be unique!", desc.kernel->name, i);
                    return false;
                }
            }

            copy.args[i] = arg;
            buffers[num_buffers++] = buf;
        } else if (info.type == arg_type::shared_buffer) {
            uint32_t align = (uint32_t)arg.data[1];
            if (align < 4) align = 4;

            uint32_t aligned_size = ((uint32_t)arg.data[0] + (align - 1)) & ~(align - 1);
            copy.args[i].data[0] = aligned_size;
            copy.args[i].data[1] = shared_size;

            if (UINT32_MAX - aligned_size < shared_size) {
                errorf("%s: Shared memory size overflows uint32", desc.kernel->name);
				return false;
            }

            shared_size += aligned_size;

        } else {
            errorf("%s: Unknown argument type at %zu: %u", desc.kernel->name, i, (uint32_t)info.type);
            return false;
        }
    }

    if (shared_size > shared_memory_size) {
        errorf("%s: Using too much shared memory: %u bytes (max %u bytes requested in gp::device_desc)",
            desc.kernel->name, shared_size, shared_memory_size);
        return false;
    }

    uintptr_t &cached = imp->kern_cache.resolve(desc.kernel->name);

    if (!cached) {
        uintptr_t kernel = be_find_kernel(desc.kernel->name);
        if (!kernel) {
            errorf("Kernel not found: %s", desc.kernel->name);
            return false;
        }
        cached = kernel;
    }

    if (num_tiles.x != 0 && num_tiles.y != 0 && num_tiles.z != 0) {
        be_dispatch_info be_info;
        be_info.kernel = cached;
        be_info.shared_memory_bytes = shared_size;

        dispatch_opts opts_copy = opts;
        if (opts_copy.debug_offset.x > num_tiles.x) opts_copy.debug_offset.x = num_tiles.x;
        if (opts_copy.debug_offset.y > num_tiles.y) opts_copy.debug_offset.y = num_tiles.y;
        if (opts_copy.debug_offset.z > num_tiles.z) opts_copy.debug_offset.z = num_tiles.z;

        gp_uint3 max_debug_extent = num_tiles - opts_copy.debug_offset;
        if (opts_copy.debug_extent.x > max_debug_extent.x) opts_copy.debug_extent.x = max_debug_extent.x;
        if (opts_copy.debug_extent.y > max_debug_extent.y) opts_copy.debug_extent.y = max_debug_extent.y;
        if (opts_copy.debug_extent.z > max_debug_extent.z) opts_copy.debug_extent.z = max_debug_extent.z;

        if (!be_dispatch(num_tiles, be_info, copy, opts_copy)) return false;
    }

    return true;
}

bool device_base::finish()
{
    mutex_guard mg(imp->mutex);

    if (!be_finish()) return false;

    return true;
}

ref<error_base> device_base::peek_errors()
{
    mutex_guard mg(imp->error_mutex);
    return imp->error_head;
}

ref<error_base> device_base::pop_errors()
{
    mutex_guard mg(imp->error_mutex);
    ref<error_base> err = std::move(imp->error_head);
    imp->error_head = ref<error_base>();
    imp->error_tail = ref<error_base>();
    return err;
}

// -- CPU backend

#ifndef GP_NO_CPU

struct cpu_device;

struct cpu_dispatch
{
    dispatch_desc desc;
    gp_uint3 num_tiles_total;
    gp_uint3 num_tiles_region;
    gp_uint3 region_offset;
    std::atomic_uint32_t counter;
    uint32_t counter_end;
};

struct cpu_worker
{
    enum task
    {
        none,
        shutdown,
        process_dispatch,
    };

    cpu_device *device = nullptr;
    std::thread thread;
    std::mutex mutex;
    std::condition_variable cvar;
    task next_task = none;
    std::unique_ptr<uint64_t> shared_mem;

    void init(cpu_device *dev, size_t shared_mem_bytes) {
        device = dev;
        mutex.lock();
        thread = std::thread(&cpu_worker::entry, this);
        shared_mem.reset(new uint64_t[(shared_mem_bytes + 7) / 8]);
    }

    void wake(task t) {
        next_task = t;
        cvar.notify_one();
        mutex.unlock();
    }

    void wait() {
        mutex.lock();
    }

    void entry();
};

struct cpu_buffer : buffer_base
{
    bool adopted = false;

    cpu_buffer(device_base *device, const buffer_desc &desc)
        : buffer_base(device, desc) { }
    virtual ~cpu_buffer() override;
    virtual bool be_init(const buffer_desc &desc, be_init_info &info) override;
    virtual bool be_read(void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_write(const void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes) override;
};

struct cpu_device : device_base
{
    std::unique_ptr<cpu_worker[]> workers;
    std::unique_ptr<uint64_t> shared_mem;
    size_t num_workers = 0;
    cpu_dispatch current_dispatch;

    virtual ~cpu_device() override;
    virtual const char *be_name() override;
    virtual bool be_get_info(device_info &info) override;
    virtual bool be_init(const device_desc &desc) override;
    virtual bool be_add_module(const module_desc &desc) override;
    virtual buffer_base *be_create_buffer(const buffer_desc &desc) override;
    virtual uintptr_t be_find_kernel(const char *name) override;
    virtual bool be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts) override;
    virtual bool be_finish() override;

    void fork_workers(cpu_worker::task task, size_t count=SIZE_MAX);
    void join_workers(size_t count=SIZE_MAX);
    void dispatch_region(const gp_uint3 &offset, const gp_uint3 &end_offset, const dispatch_desc &desc, const dispatch_opts &opts);
    void process_dispatch(void *shared_memory);
};

cpu_buffer::~cpu_buffer()
{
    if (cpu_data && !adopted) free(cpu_data);
}

bool cpu_buffer::be_init(const buffer_desc &desc, be_init_info &info)
{
    if (desc.device_pointer) {
        cpu_data = desc.device_pointer;
        adopted = true;
        return true;
    }

    cpu_data = malloc(size_bytes);
    if (!cpu_data) {
        device->errorf("Out of CPU memory, trying to allocate %zu bytes", desc.size_bytes);
        return false;
    }

    return true;
}

bool cpu_buffer::be_read(void *data, size_t offset_bytes, size_t size_bytes)
{
    memcpy(data, (const char*)cpu_data + offset_bytes, size_bytes);
    return true;
}

bool cpu_buffer::be_write(const void *data, size_t offset_bytes, size_t size_bytes)
{
    memcpy((char*)cpu_data + offset_bytes, data, size_bytes);
    return true;
}

bool cpu_buffer::be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes)
{
    memset((char*)cpu_data + offset_bytes, value, size_bytes);
    return true;
}

cpu_device::~cpu_device()
{
    fork_workers(cpu_worker::shutdown);
    for (size_t i = 0; i < num_workers; i++) {
        workers[i].thread.join();
    }
}

const char *cpu_device::be_name()
{
    return "cpu";
}

bool cpu_device::be_get_info(device_info &info)
{
    char *end = gp_get_cpu_name(info.device, sizeof(info.device));
    while (end > info.device && (uint8_t)end[-1] <= (uint8_t)' ') end--;
    *end = '\0';

    return true;
}

bool cpu_device::be_init(const device_desc &desc)
{
    size_t num_threads = desc.num_threads;
    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
    }

    shared_mem.reset(new uint64_t[(shared_memory_size + 7) / 8]);

    if (num_threads > 1) {
        num_workers = num_threads - 1;
        workers.reset(new cpu_worker[num_workers]);
        for (size_t i = 0; i < num_workers; i++) {
            workers[i].init(this, shared_memory_size);
        }
    }

    return true;
}

bool cpu_device::be_add_module(const module_desc &desc)
{
    return true;
}

buffer_base *cpu_device::be_create_buffer(const buffer_desc &desc)
{
    return new cpu_buffer(this, desc);
}

uintptr_t cpu_device::be_find_kernel(const char *name)
{
    return 1;
}

bool cpu_device::be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts)
{
    if (!desc.kernel->cpu_func) {
        errorf("Kernel doesn't have a CPU implementation: %s", desc.kernel->name);
        return false;
    }

    gp_uint3 offset = { };
    current_dispatch.num_tiles_total = num_tiles;
    dispatch_region(offset, num_tiles, desc, opts);

    return true;
}

bool cpu_device::be_finish()
{
    return true;
}

void cpu_device::fork_workers(cpu_worker::task task, size_t count)
{
    if (count > num_workers) count = num_workers;
    for (size_t i = 0; i < count; i++) {
        workers[i].wake(task);
    }
}

void cpu_device::join_workers(size_t count)
{
    if (count > num_workers) count = num_workers;
    for (size_t i = 0; i < count; i++) {
        workers[i].wait();
    }
}

void cpu_device::dispatch_region(const gp_uint3 &offset, const gp_uint3 &end_offset, const dispatch_desc &desc, const dispatch_opts &opts)
{
    gp_uint3 num_tiles = end_offset - offset;
    if (num_tiles.x == 0 || num_tiles.y == 0 || num_tiles.z == 0) return;

    if (opts.debug_extent.x > 0 && opts.debug_extent.y > 0 && opts.debug_extent.z > 0) {
        dispatch_opts copy = opts;
        copy.debug_extent = gp_uint3();

        gp_uint3 p0 = offset;
        gp_uint3 p1 = opts.debug_offset;
        gp_uint3 p2 = p1 + opts.debug_extent;
        gp_uint3 p3 = p0 + num_tiles;

        dispatch_region({ p0.x, p0.y, p0.z }, { p3.x, p3.y, p1.z }, desc, copy);
        dispatch_region({ p0.x, p0.y, p2.z }, { p3.x, p3.y, p3.z }, desc, copy);

        dispatch_region({ p0.x, p0.y, p1.z }, { p3.x, p1.y, p2.z }, desc, copy);
        dispatch_region({ p0.x, p2.y, p1.z }, { p3.x, p3.y, p2.z }, desc, copy);

        dispatch_region({ p0.x, p1.y, p1.z }, { p1.x, p2.y, p2.z }, desc, copy);
        dispatch_region({ p2.x, p1.y, p1.z }, { p3.x, p2.y, p2.z }, desc, copy);

        copy.max_threads = 1;

        // vvv BREAKPOINT HERE vvv
        dispatch_region({ p1.x, p1.y, p1.z }, { p2.x, p2.y, p2.z }, desc, copy);
        // ^^^ BREAKPOINT HERE ^^^

        return;
    }

    uint32_t dim_left = UINT32_MAX / num_tiles.x / num_tiles.y / num_tiles.z;
    if (dim_left <= 1) {
        gp_uint3 sub_dim = num_tiles / 2;
        gp_uint3 mid = offset + sub_dim;
        for (size_t i = 0; i < 8; i++) {
            gp_uint3 off = offset, end = mid;
            if (i & 0x1) { off.x = mid.x; end.x = end_offset.x; }
            if (i & 0x2) { off.y = mid.y; end.y = end_offset.y; }
            if (i & 0x4) { off.z = mid.z; end.z = end_offset.z; }
            dispatch_region(off, end, desc, opts);
        }
        return;
    }

    current_dispatch.desc = desc;
    current_dispatch.region_offset = offset;
    current_dispatch.num_tiles_region = num_tiles;
    current_dispatch.counter.store(0, std::memory_order_relaxed);
    current_dispatch.counter_end = num_tiles.x * num_tiles.y * num_tiles.z;

    size_t num_dispatch_workers = current_dispatch.counter_end - 1;

    if (opts.max_threads > 0 && num_dispatch_workers > opts.max_threads - 1) {
        num_dispatch_workers = opts.max_threads - 1;
    }

    fork_workers(cpu_worker::process_dispatch, num_dispatch_workers);
    process_dispatch(shared_mem.get());
    join_workers(num_dispatch_workers);
}

void cpu_device::process_dispatch(void *shared_memory)
{
    cpu_dispatch &cd = current_dispatch;

    tile_indices indices;
    indices.shared_memory = shared_memory;
    indices.num_tiles = cd.num_tiles_total;

    uint32_t div_y = cd.num_tiles_region.x;
    uint32_t div_z = cd.num_tiles_region.x * cd.num_tiles_region.y;

    gp_uint3 off = cd.region_offset;
    const kernel_info *kern = cd.desc.kernel;

    for (;;) {
        uint32_t index = cd.counter.fetch_add(1u, std::memory_order_relaxed);
        if (index >= cd.counter_end) break;

        indices.tile_index.x = off.x + index % cd.num_tiles_region.x;
        indices.tile_index.y = off.y + index / div_y % cd.num_tiles_region.y;
        indices.tile_index.z = off.z + index / div_z;
        indices.tile_offset.x = indices.tile_index.x * kern->tile_size[0];
        indices.tile_offset.y = indices.tile_index.y * kern->tile_size[1];
        indices.tile_offset.z = indices.tile_index.z * kern->tile_size[2];

        kern->cpu_func(indices, cd.desc.args);
    }
}

void cpu_worker::entry()
{
    std::unique_lock<std::mutex> ul(mutex);
    for (;;) {
        while (next_task == none) {
            cvar.wait(ul);
        }

        switch (next_task) {

        case none:
            gp_assert(0 && "Should not get here");
            break;

        case shutdown:
            return;

        case process_dispatch:
            device->process_dispatch(shared_mem.get());
            break;

        }

        next_task = none;
    }
}

#endif

// -- OpenCL backend

#ifdef GP_USE_OPENCL

struct opencl_temp_mems
{
    cl_mem mems[max_args];
    size_t count = 0;

    ~opencl_temp_mems() {
        for (size_t i = 0; i < count; i++) {
            clReleaseMemObject(mems[i]);
        }
    }

    void add(cl_mem mem) {
        gp_assert(count < max_args);
        mems[count++] = mem;
    }
};

template <typename T>
T opencl_device_info(cl_device_id did, cl_device_info info, T missing)
{
    T t;
    cl_int err = clGetDeviceInfo(did, info, sizeof(t), &t, nullptr);
    return err == CL_SUCCESS ? t : missing;
}

double opencl_score_device(const device_desc &desc, cl_device_id did)
{
    double score = 0.0;

    if (!opencl_device_info(did, CL_DEVICE_AVAILABLE, cl_bool(false))) return bad_score;
    if (!opencl_device_info(did, CL_DEVICE_COMPILER_AVAILABLE, cl_bool(false))) return bad_score;
    if (opencl_device_info(did, CL_DEVICE_LOCAL_MEM_SIZE, cl_ulong(0)) < desc.shared_memory_size) return bad_score;
    score += at_most(1e6,
        (double)opencl_device_info(did, CL_DEVICE_MAX_COMPUTE_UNITS, cl_uint(0)) *
        (double)opencl_device_info(did, CL_DEVICE_MAX_CLOCK_FREQUENCY, cl_uint(0)));

    return score;
}

struct opencl_buffer : buffer_base
{
    cl_mem mem = nullptr;
    bool adopted = false;

    opencl_buffer(device_base *device, const buffer_desc &desc) : buffer_base(device, desc) { }
    virtual ~opencl_buffer() override;
    virtual bool be_init(const buffer_desc &desc, be_init_info &info) override;
    virtual bool be_read(void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_write(const void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes) override;
};

struct opencl_device : device_base
{
    cl_platform_id platform = nullptr;
    cl_device_id device = nullptr;
    cl_context context = nullptr;
    cl_command_queue queue = nullptr;
    bool device_adopted = false;
    bool context_adopted = false;
    bool queue_adopted = false;
    std::vector<cl_program> programs;
    std::vector<cl_kernel> kernels;

    virtual ~opencl_device() override;
    virtual const char *be_name() override;
    virtual bool be_get_info(device_info &info) override;
    virtual bool be_init(const device_desc &desc) override;
    virtual bool be_add_module(const module_desc &desc) override;
    virtual buffer_base *be_create_buffer(const buffer_desc &desc) override;
    virtual uintptr_t be_find_kernel(const char *name) override;
    virtual bool be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts) override;
    virtual bool be_finish() override;
};

opencl_buffer::~opencl_buffer()
{
    if (mem && !adopted) {
        clReleaseMemObject(mem);
    }
}

bool opencl_buffer::be_init(const buffer_desc &desc, be_init_info &info)
{
    if (desc.device_pointer) {
        mem = (cl_mem)desc.device_pointer;
        adopted = true;
        return true;
    }

    opencl_device *dev = (opencl_device*)device;

    cl_mem_flags flags = 0;
    void *host_ptr = nullptr;
    if (desc.initial_data_bytes == desc.size_bytes) {
        info.initial_copied = true;
        host_ptr = (void*)desc.initial_data;
        flags |= CL_MEM_COPY_HOST_PTR;
    }

    cl_int err;
    mem = clCreateBuffer(dev->context, flags, desc.size_bytes, host_ptr, &err);
    if (!mem) {
        if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
            dev->errorf("Out of GPU memory, trying to allocate %zu bytes", desc.size_bytes);
        } else {
            dev->errorf("clCreateBuffer(%zu bytes) failed: %d", desc.size_bytes, err);
        }
        return false;
    }

    return true;
}

bool opencl_buffer::be_read(void *data, size_t offset_bytes, size_t size_bytes)
{
    opencl_device *dev = (opencl_device*)device;

    cl_int err = clEnqueueReadBuffer(dev->queue, mem, CL_TRUE,
        offset_bytes, size_bytes, data, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        dev->errorf("clEnqueueReadBuffer() failed: %d", err);
        return false;
    }

    return true;
}

bool opencl_buffer::be_write(const void *data, size_t offset_bytes, size_t size_bytes)
{
    opencl_device *dev = (opencl_device*)device;

    cl_int err = clEnqueueWriteBuffer(dev->queue, mem, CL_TRUE,
        offset_bytes, size_bytes, data, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        dev->errorf("clEnqueueWriteBuffer() failed: %d", err);
        return false;
    }

    return true;
}

bool opencl_buffer::be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes)
{
    opencl_device *dev = (opencl_device*)device;

    char pat[1] = { (char)value };
    cl_int err = clEnqueueFillBuffer(dev->queue, mem, pat, 1,
        offset_bytes, size_bytes, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        dev->errorf("clEnqueueFillBuffer() failed: %d", err);
        return false;
    }

    return true;
}

opencl_device::~opencl_device()
{
    for (cl_kernel k : kernels) clReleaseKernel(k);
    for (cl_program p : programs) clReleaseProgram(p);
    if (queue && !queue_adopted) clReleaseCommandQueue(queue);
    if (context && !context_adopted) clReleaseContext(context);
}

const char *opencl_device::be_name()
{
    return "opencl";
}

bool opencl_device::be_get_info(device_info &info)
{
    cl_int err;
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(info.device), info.device, nullptr);
    if (err != CL_SUCCESS) {
        errorf("clGetDeviceInfo(CL_DEVICE_NAME) failed: %d", err);
        return false;
    }
    return true;
}

bool opencl_device::be_init(const device_desc &desc)
{
    cl_int err;
    cl_uint num;

    if (desc.opencl_device_id) {
        device_adopted = true;
        device = (cl_device_id)desc.opencl_device_id;

        err = clGetDeviceInfo(device, CL_DEVICE_PLATFORM, sizeof(cl_platform_id), &platform, nullptr);
        if (err != CL_SUCCESS) {
            errorf("clGetDeviceInfo(CL_DEVICE_PLATFORM) failed: %d", err);
            return false;
        }

        if (opencl_score_device(desc, device) == bad_score) {
            errorf("User-supplied OpenCL device does not meet desc requirements");
            return false;
        }

    } else {

        std::vector<cl_platform_id> platforms;

        err = clGetPlatformIDs(0, nullptr, &num);
        if (err == CL_SUCCESS) {
            platforms.resize(num);
            err = clGetPlatformIDs(num, platforms.data(), nullptr);
        }
        if (err != CL_SUCCESS) {
            warnf("clGetPlatformIDs() failed: %d, OpenCL not available?", err);
            return false;
        }

        cl_platform_id best_platform = 0;
        cl_device_id best_device = 0;
        double best_score = bad_score;

        std::vector<cl_device_id> devices;
        for (cl_platform_id pid : platforms) {
            err = clGetDeviceIDs(pid, CL_DEVICE_TYPE_ALL, 0, nullptr, &num);
            if (err == CL_SUCCESS) {
                devices.resize(num);
                err = clGetDeviceIDs(pid, CL_DEVICE_TYPE_ALL, num, devices.data(), nullptr);
            }
            if (err != CL_SUCCESS) {
                warnf("clGetDeviceIDs() failed: %d", err);
                continue;
            }

            for (cl_device_id did : devices) {
                double score = opencl_score_device(desc, did);
                if (score > best_score) {
                    best_platform = pid;
                    best_device = did;
                    best_score = score;
                }
            }
        }

        if (best_score == bad_score) {
            warnf("Could not find a suitable OpenCL device");
            return false;
        }

        platform = best_platform;
        device = best_device;

    }

    if (desc.opencl_context) {
        context_adopted = true;
        context = (cl_context)desc.opencl_context;
    } else {
        cl_context_properties props[] = {
            (cl_context_properties)CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform,
            0, 0,
        };

        context = clCreateContext(props, 1, &device, nullptr, nullptr, &err);
        if (!context) {
            errorf("clCreateContext() failed: %d", err);
            return false;
        }
    }

    if (desc.opencl_command_queue) {
        queue_adopted = true;
        queue = (cl_command_queue)desc.opencl_command_queue;
    } else {
        queue = clCreateCommandQueue(context, device, 0, &err);
        if (!queue) {
            errorf("clCreateCommandQueue() failed: %d", err);
            return false;
        }
    }

    return true;
}

bool opencl_device::be_add_module(const module_desc &desc)
{
    if (desc.type == module_type::opencl_source) {
        char buffer[128];
        cl_int err = 0;

        size_t prefix_len = snprintf(buffer, sizeof(buffer), "#line 1 \"%s\"\n", desc.name);
        const char *strings[] = { buffer, (const char*)desc.data };
        size_t lengths[] = { prefix_len, desc.size };

        cl_program program = clCreateProgramWithSource(context, 2, strings, lengths, &err);
        if (err != CL_SUCCESS) {
            errorf("clCreateProgramWithSource() '%s' failed: %d", desc.name, err);
            return false;
        }

        err = clBuildProgram(program, 1, &device, desc.opts, nullptr, nullptr);
        if (err != CL_SUCCESS) {
            cl_int err2 = -1;
            if (err == CL_BUILD_PROGRAM_FAILURE) {
                std::vector<char> error_buf;
                size_t error_len = 0;

                err2 = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &error_len);
                if (err2 == CL_SUCCESS) {
                    error_buf.resize(error_len + 1);
                    err2 = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                        error_len, error_buf.data(), nullptr);
                    if (err2 == CL_SUCCESS) {
                        errorf("OpenCL compile '%s' failed:\n%s", desc.name, error_buf.data());
                    }
                }

                if (err2 != CL_SUCCESS) {
                    warnf("clGetProgramBuildInfo() failed: %d", err2);
                }
            }

            if (err2 != CL_SUCCESS) {
                errorf("OpenCL compile '%s' failed: %d", desc.name, err);
            }
            clReleaseProgram(program);
            return false;
        }

        programs.push_back(program);

        return true;
    } else {
        return true;
    }
}

buffer_base *opencl_device::be_create_buffer(const buffer_desc &desc)
{
    return new opencl_buffer(this, desc);
}

uintptr_t opencl_device::be_find_kernel(const char *name)
{
    for (cl_program p : programs) {
        cl_int err;
        cl_kernel kernel = clCreateKernel(p, name, &err);
        if (err == CL_SUCCESS) {
            kernels.push_back(kernel);
            return (uintptr_t)kernel;
        } else if (err != CL_INVALID_KERNEL_NAME) {
            warnf("clCreateKernel(\"%s\") failed: %d", name, err);
        }
    }
    return 0;
}

bool opencl_device::be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts)
{
    cl_kernel kern = (cl_kernel)be_info.kernel;
    const kernel_info *info = desc.kernel;
    cl_int err = 0;

    opencl_temp_mems temp_mems;

    for (cl_uint i = 0; i < info->num_args; i++) {
        const arg_info &arg_info = info->args[i];
        arg_ptr arg = desc.args[i];
        switch (arg_info.type) {

        case arg_type::constant: {
            err = clSetKernelArg(kern, i, arg_info.size, (const void*)arg.data[0]);
            if (err != CL_SUCCESS) {
                errorf("%s: clSetKernelArg(%d) constant failed: %d", info->name, i, err);
                return false;
            }
        } break;

        case arg_type::buffer: {
            const opencl_buffer *buf = (opencl_buffer*)arg.data[0];

            cl_mem mem = buf->mem;
            size_t offset = (size_t)arg.data[1];
            if (offset > 0) {
                cl_buffer_region region = { offset, buf->size_bytes - offset };
                mem = clCreateSubBuffer(mem, CL_MEM_READ_WRITE,
                    CL_BUFFER_CREATE_TYPE_REGION, &region, &err);
                if (!mem) {
                    errorf("%s: clCreateSubBuffer(%d) failed: %d", info->name, err);
                    return false;
                }
                temp_mems.add(mem);
            }

            err = clSetKernelArg(kern, i, sizeof(cl_mem), &mem);
            if (err != CL_SUCCESS) {
                errorf("%s: clSetKernelArg(%d) buffer failed: %d", info->name, i, err);
                return false;
            }
        } break;

        case arg_type::shared_buffer: {
            size_t shared_size = (size_t)arg.data[0];

            err = clSetKernelArg(kern, i, shared_size, nullptr);
            if (err != CL_SUCCESS) {
                errorf("%s: clSetKernelArg(%d) buffer failed: %d", info->name, i, err);
                return false;
            }
        } break;

        }
    }

    size_t global_offset[3] = { };
    size_t local_size[3] = { desc.kernel->tile_size[0], desc.kernel->tile_size[1], desc.kernel->tile_size[2] };
    size_t global_size_sz[3] = { num_tiles.x * local_size[0], num_tiles.y * local_size[1], num_tiles.z * local_size[2] };
    err = clEnqueueNDRangeKernel(queue, kern, 3,
        global_offset, global_size_sz, local_size,
        0, nullptr, nullptr);

    if (err != CL_SUCCESS) {
        errorf("%s: clEnqueueNDRangeKernel() failed: %d", info->name, err);
        return false;
    }

    return true;
}

bool opencl_device::be_finish()
{
    cl_int err = clFinish(queue);
    if (err != CL_SUCCESS) {
        errorf("clFinish() failed: %d", err);
        return false;
    }

    return true;
}

#endif

// -- CUDA backend

#ifdef GP_USE_CUDA

int cuda_device_attrib(CUdevice dev, CUdevice_attribute attrib, int missing)
{
    int data = missing;
    CUresult res = cuDeviceGetAttribute(&data, attrib, dev);
    return res == CUDA_SUCCESS ? data : missing;
}

double cuda_score_device(const device_desc &desc, CUdevice dev)
{
    double score = 0.0;

    if (cuda_device_attrib(dev, CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK, 0) < desc.shared_memory_size) return bad_score;

    score += at_most(1e6,
        (double)cuda_device_attrib(dev, CU_DEVICE_ATTRIBUTE_CLOCK_RATE, 0) * 1e-3 *
        (double)cuda_device_attrib(dev, CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, 0));

    return score;
}

union cuda_arg_union
{
    CUdeviceptr buffer_ptr;
    uint32_t shared_offset;
};

struct cuda_buffer : buffer_base
{
    CUdeviceptr device_ptr = 0;
    bool adopted = false;

    cuda_buffer(device_base *device, const buffer_desc &desc) : buffer_base(device, desc) { }
    virtual ~cuda_buffer() override;
    virtual bool be_init(const buffer_desc &desc, be_init_info &info) override;
    virtual bool be_read(void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_write(const void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes) override;
};

struct cuda_device : device_base
{
    int device_index = -1;
    CUdevice device = -1;
    CUcontext context = nullptr;
    CUstream stream = nullptr;
    bool device_adopted = false;
    bool context_adopted = false;
    bool stream_adopted = false;
    std::vector<CUmodule> modules;

    virtual ~cuda_device() override;
    virtual const char *be_name() override;
    virtual bool be_get_info(device_info &info) override;
    virtual bool be_init(const device_desc &desc) override;
    virtual bool be_add_module(const module_desc &desc) override;
    virtual buffer_base *be_create_buffer(const buffer_desc &desc) override;
    virtual uintptr_t be_find_kernel(const char *name) override;
    virtual bool be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts) override;
    virtual bool be_finish() override;
};

struct cuda_ctx
{
    CUcontext prev = nullptr;
    bool ok = false;

    cuda_ctx(device_base *dev) {
        CUresult res = cuCtxGetCurrent(&prev);
        if (res != CUDA_SUCCESS) {
            dev->errorf("cuCtxGetCurrent() failed: %d", res);
            prev = nullptr;
        } else {
            res = cuCtxSetCurrent(((cuda_device*)dev)->context);
            if (res != CUDA_SUCCESS) {
                dev->errorf("cuCtxSetCurrent() failed: %d", res);
            } else {
                ok = true;
            }
        }
    }
    ~cuda_ctx() { if (prev) cuCtxSetCurrent(prev); }
    explicit operator bool() { return ok; }
};

cuda_buffer::~cuda_buffer()
{
    if (device_ptr && !adopted) {
        cuda_device *dev = (cuda_device*)device;
        cuda_ctx cctx { device };
        if (cctx) cuMemFree(device_ptr);
    }
}

bool cuda_buffer::be_init(const buffer_desc &desc, be_init_info &info)
{
    if (desc.device_pointer) {
        device_ptr = (CUdeviceptr)desc.device_pointer;
        adopted = true;
        return true;
    }

    cuda_device *dev = (cuda_device*)device;
    cuda_ctx cctx { device };
    if (!cctx) return false;

    CUresult res = cuMemAlloc(&device_ptr, desc.size_bytes);
    if (res != CUDA_SUCCESS) {
        if (res == CUDA_ERROR_OUT_OF_MEMORY) {
            dev->errorf("Out of GPU memory, trying to allocate %zu bytes", desc.size_bytes);
        } else {
            dev->errorf("cuMemAlloc(%zu) failed: %d", desc.size_bytes, res);
        }
        return false;
    }

    return true;
}

bool cuda_buffer::be_read(void *data, size_t offset_bytes, size_t size_bytes)
{
    cuda_device *dev = (cuda_device*)device;
    cuda_ctx cctx { device };
    if (!cctx) return false;

    CUresult res = cuMemcpyDtoHAsync(data, device_ptr + offset_bytes, size_bytes, dev->stream);
    if (res != CUDA_SUCCESS) {
        dev->errorf("cuMemcpyDtoH failed: %d", res);
        return false;
    }

    return true;
}

bool cuda_buffer::be_write(const void *data, size_t offset_bytes, size_t size_bytes)
{
    cuda_device *dev = (cuda_device*)device;

    {
        cuda_ctx cctx { device };
        if (!cctx) return false;

        CUresult res = cuMemcpyHtoDAsync(device_ptr + offset_bytes, data, size_bytes, dev->stream);
        if (res != CUDA_SUCCESS) {
            dev->errorf("cuMemcpyHtoD failed: %d", size_bytes, res);
            return false;
        }
    }

    // TODO: This is probably not required (?)
    return dev->be_finish();
}

bool cuda_buffer::be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes)
{
    cuda_device *dev = (cuda_device*)device;
    cuda_ctx cctx { device };
    if (!cctx) return false;

    CUresult res = cuMemsetD8Async(device_ptr + offset_bytes, value, size_bytes, dev->stream);
    if (res != CUDA_SUCCESS) {
        dev->errorf("cuMemsetD8Async failed: %d", size_bytes, res);
        return false;
    }

    return true;
}

cuda_device::~cuda_device()
{
    if (stream) cuStreamSynchronize(stream);
    for (CUmodule m : modules) cuModuleUnload(m);
    if (stream && !stream_adopted) cuStreamDestroy(stream);
    if (context && !context_adopted) cuCtxDestroy(context);
}

const char *cuda_device::be_name()
{
    return "cuda";
}

bool cuda_device::be_get_info(device_info &info)
{
    CUresult res;
    res = cuDeviceGetName(info.device, (int)sizeof(info.device), device);
    if (res != CUDA_SUCCESS) {
        errorf("cuDeviceGetName() failed: %d", res);
        return false;
    }
    return true;
}

bool cuda_device::be_init(const device_desc &desc)
{
    unsigned flags = 0;
    CUresult res;

    if (desc.cuda_device >= 0) {
        device_adopted = true;
        device = (CUdevice)desc.cuda_device;

        if (cuda_score_device(desc, device) == bad_score) {
            errorf("User-supplied CUDA device does not meet desc requirements");
            return false;
        }

    } else {
        int num_devices = 0;
        res = cuDeviceGetCount(&num_devices);
        if (res != CUDA_SUCCESS) {
            warnf("cuDeviceGetCount() failed: %d, CUDA not supported?", res);
            return false;
        }

        CUdevice best_device = 0;
        double best_score = bad_score;

        for (int i = 0; i < num_devices; i++) {
            CUdevice dev;
            res = cuDeviceGet(&dev, i);
            if (res != CUDA_SUCCESS) {
                warnf("cuDeviceGet(%d) failed: %d", i, res);
                continue;
            }

            double score = cuda_score_device(desc, dev);
            if (score > best_score) {
                best_device = dev;
                best_score = score;
            }
        }

        if (best_score == bad_score) {
            warnf("No suitable CUDA devices found");
            return false;
        }

        device = best_device;
    }

    if (desc.cuda_context) {
        context_adopted = true;
        context = (CUcontext)desc.cuda_context;
    } else {
        flags |= desc.prefer_spin_wait ? CU_CTX_SCHED_SPIN : CU_CTX_SCHED_YIELD;

        res = cuCtxCreate(&context, flags, device);
        if (res != CUDA_SUCCESS) {
            errorf("cuCtxCreate() failed: %d", res);
            return false;
        }
    }

    cuda_ctx cctx { this };
    if (!cctx) return false;

    if (desc.cuda_stream) {
        stream_adopted = true;
        stream = (CUstream)desc.cuda_stream;
    } else {
        res = cuStreamCreate(&stream, CU_STREAM_DEFAULT);
        if (res != CUDA_SUCCESS) {
            errorf("cuStreamCreate() failed: %d", res);
            return false;
        }
    }

    return true;
}

bool cuda_device::be_add_module(const module_desc &desc)
{
    if (desc.type != module_type::cuda_binary) return true;
    cuda_ctx cctx { this };

    CUmodule mod;
    CUresult res = cuModuleLoadData(&mod, desc.data);
    if (res != CUDA_SUCCESS) {
        errorf("Failed to load CUDA module '%s': %d", desc.name, res);
        return false;
    }

    modules.push_back(mod);
    return true;
}

buffer_base *cuda_device::be_create_buffer(const buffer_desc &desc)
{
    return new cuda_buffer(this, desc);
}

uintptr_t cuda_device::be_find_kernel(const char *name)
{
    cuda_ctx cctx { this };

    for (CUmodule mod : modules) {
        CUfunction func;
        CUresult res = cuModuleGetFunction(&func, mod, name);
        if (res == CUDA_SUCCESS) {
            return (uintptr_t)func;
        } else if (res != CUDA_ERROR_NOT_FOUND) {
            warnf("cuModuleGetFunction(\"%s\") failed: %d", name, res);
        }
    }

    return 0;
}

bool cuda_device::be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts)
{
    cuda_ctx cctx { this };
    CUfunction func = (CUfunction)be_info.kernel;
    const kernel_info *info = desc.kernel;

    void *params[max_args];
    cuda_arg_union arg_unions[max_args];

    for (size_t i = 0; i < info->num_args; i++) {
        const arg_info &arg_info = info->args[i];
        arg_ptr arg = desc.args[i];
        switch (arg_info.type) {

        case arg_type::constant: {
            params[i] = (void*)arg.data[0];
        } break;

        case arg_type::buffer: {
            const cuda_buffer *buf = (cuda_buffer*)arg.data[0];
            size_t offset = (size_t)arg.data[1];
            arg_unions[i].buffer_ptr = buf->device_ptr + offset;
            params[i] = &arg_unions[i].buffer_ptr;
        } break;

        case arg_type::shared_buffer: {
            uint32_t offset = (uint32_t)arg.data[1];
            gp_assert(offset % 4 == 0);
            arg_unions[i].shared_offset = offset / 4;
            params[i] = &arg_unions[i].shared_offset;
        } break;

        }
    }

    uint32_t tile_sz_x = desc.kernel->tile_size[0];
    uint32_t tile_sz_y = desc.kernel->tile_size[1];
    uint32_t tile_sz_z = desc.kernel->tile_size[2];

    CUresult res = cuLaunchKernel(func,
        num_tiles.x, num_tiles.y, num_tiles.z,
        tile_sz_x, tile_sz_y, tile_sz_z,
        be_info.shared_memory_bytes, stream, params, nullptr);

    if (res != CUDA_SUCCESS) {
        errorf("%s: cuLaunchKernel() failed: %d", info->name, res);
        return false;
    }

    return true;
}

bool cuda_device::be_finish()
{
    cuda_ctx cctx { this };

    CUresult res = cuStreamSynchronize(stream);
    if (res != CUDA_SUCCESS) {
        errorf("cuStreamSynchronize() failed: %d", res);
        return false;
    }

    return true;
}

#endif

// -- Metal backend

#ifdef GP_USE_METAL

struct metal_device;
struct metal_buffer;

struct metal_locked_buffer
{
    metal_buffer *buffer = nullptr;
    void *data = nullptr;
    bool needs_flush = false;
    size_t offset = 0;
    size_t size = 0;
    id<MTLBuffer> staging = nil;

    explicit operator bool() const { return data; }
    bool operator!() const { return !data; }

    ~metal_locked_buffer() {
        if (staging) {
            @autoreleasepool {
                staging = nil;
            }
        }
    }

    bool flush();
};

struct metal_buffer : buffer_base
{
    id<MTLBuffer> buffer = nil;
    MTLStorageMode storage = MTLStorageModePrivate;

    metal_buffer(device_base *device, const buffer_desc &desc) : buffer_base(device, desc) { }
    virtual ~metal_buffer() override;
    virtual bool be_init(const buffer_desc &desc, be_init_info &info) override;
    virtual bool be_read(void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_write(const void *data, size_t offset_bytes, size_t size_bytes) override;
    virtual bool be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes) override;

    metal_locked_buffer lock(size_t offset, size_t size, const void *data=nullptr);
};

struct metal_device : device_base
{
    id<MTLDevice> device = nil;
    id<MTLCommandQueue> queue = nil;
    id<MTLCommandBuffer> command_buffer = nil;
    id<MTLComputeCommandEncoder> compute_encoder = nil;
    id<MTLBlitCommandEncoder> blit_encoder = nil;
    std::vector<id<MTLLibrary>> libraries;
    std::vector<id<MTLComputePipelineState>> pipelines;

    virtual ~metal_device() override;
    virtual const char *be_name() override;
    virtual bool be_get_info(device_info &info) override;
    virtual bool be_init(const device_desc &desc) override;
    virtual bool be_add_module(const module_desc &desc) override;
    virtual buffer_base *be_create_buffer(const buffer_desc &desc) override;
    virtual uintptr_t be_find_kernel(const char *name) override;
    virtual bool be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts) override;
    virtual bool be_finish() override;

    void end_encoding();
    id<MTLCommandBuffer> start_commands();
    id<MTLComputeCommandEncoder> start_compute();
    id<MTLBlitCommandEncoder> start_blit();
};

bool metal_locked_buffer::flush()
{
    if (!needs_flush) return true;

    if (staging) {
        metal_device *dev = (metal_device*)buffer->device;
        id<MTLBlitCommandEncoder> encoder = dev->start_blit();
        if (!encoder) return false;
        [encoder copyFromBuffer:staging sourceOffset:0
            toBuffer:buffer->buffer destinationOffset:offset size:size];
        return dev->be_finish();
    } else {
        [buffer->buffer didModifyRange:NSMakeRange(offset, size)];
        return true;
    }
}

metal_buffer::~metal_buffer()
{
    @autoreleasepool {
        buffer = nil;
    }
}

bool metal_buffer::be_init(const buffer_desc &desc, be_init_info &info)
{
    if (desc.device_pointer) {
        buffer = (__bridge id<MTLBuffer>)desc.device_pointer;
        storage = [buffer storageMode];
        return true;
    }

    metal_device *dev = (metal_device*)device;

    // storage = MTLStorageModePrivate;
    storage = MTLStorageModeManaged;

    MTLResourceOptions opts = storage << MTLResourceStorageModeShift;

    if (desc.initial_data_bytes == desc.size_bytes && storage != MTLStorageModePrivate) {
        buffer = [dev->device newBufferWithBytes:desc.initial_data length:desc.size_bytes options:opts];
        info.initial_copied = true;
    } else {
        buffer = [dev->device newBufferWithLength:desc.size_bytes options:opts];
        info.zeroed = true;
    }

    return true;
}

bool metal_buffer::be_read(void *data, size_t offset_bytes, size_t size_bytes)
{
    metal_locked_buffer lb = lock(offset_bytes, size_bytes);
    if (!lb) return false;
    memcpy(data, lb.data, size_bytes);
    return true;
}

bool metal_buffer::be_write(const void *data, size_t offset_bytes, size_t size_bytes)
{
    metal_locked_buffer lb = lock(offset_bytes, size_bytes, data);
    if (!lb) return false;
    return lb.flush();
}

bool metal_buffer::be_fill(uint8_t value, size_t offset_bytes, size_t size_bytes)
{
    metal_device *dev = (metal_device*)device;
    if (offset_bytes % 4 == 0 && size_bytes % 4 == 0) {
        id<MTLBlitCommandEncoder> encoder = dev->start_blit();
        if (!encoder) return false;
        [encoder fillBuffer:buffer range:NSMakeRange(offset_bytes, size_bytes) value:value];
        return true;
    }

    metal_locked_buffer lb = lock(offset_bytes, size_bytes);
    if (!lb) return false;
    memset(lb.data, value, size_bytes);
    return true;
}

metal_locked_buffer metal_buffer::lock(size_t offset, size_t size, const void *data)
{
    metal_locked_buffer lb;

    metal_device *dev = (metal_device*)device;
    lb.buffer = this;

    size_t aligned_begin = offset & ~(size_t)3;
    size_t aligned_end = (offset + size + 3) & ~(size_t)3;
    size_t aligned_size = aligned_end - aligned_begin;

    lb.offset = aligned_begin;
    lb.size = aligned_size;

    switch (storage) {

        case MTLStorageModeShared: {
            lb.data = (char*)[buffer contents] + offset;
        } break;

        case MTLStorageModeManaged: {
            id<MTLBlitCommandEncoder> encoder = dev->start_blit();
            if (!encoder) return { };
            [encoder synchronizeResource:buffer];
            if (!dev->be_finish()) return { };
            lb.data = (char*)[buffer contents] + offset;
            lb.needs_flush = true;
        } break;

        case MTLStorageModePrivate: {
            id<MTLBuffer> staging = nil;

            if (data && aligned_size == size) {
                staging = [dev->device newBufferWithBytes:data length:size options:MTLStorageModeShared];
                data = nullptr;
            } else {
                staging = [dev->device newBufferWithLength:aligned_size options:MTLStorageModeShared];
            }
            if (!staging) {
                dev->errorf("Failed to create staging buffer");
                return { };
            }

            lb.staging = staging;

            id<MTLBlitCommandEncoder> encoder = dev->start_blit();
            if (!encoder) return { };
            [encoder copyFromBuffer:buffer sourceOffset:aligned_begin
                toBuffer:staging destinationOffset:0 size:aligned_size];
            if (!dev->be_finish()) return { };

            lb.data = (char*)[staging contents] + (offset & 3);
            lb.needs_flush = true;
        } break;

        default: {
            gp_assert(0 && "Unhanded storage mode");
        } break;

    }

    if (data) {
        memcpy(lb.data, data, size);
    }

    return lb;
}

metal_device::~metal_device()
{
    be_finish();

    @autoreleasepool {
        device = nil;
        queue = nil;
        command_buffer = nil;
    }
}

const char *metal_device::be_name()
{
    return "metal";
}

bool metal_device::be_get_info(device_info &info)
{
    const char *name = [[device name] UTF8String];
    snprintf(info.device, sizeof(info.device), "%s", name);
    return true;
}

bool metal_device::be_init(const device_desc &desc)
{
    if (desc.metal_device) {
        device = (__bridge id<MTLDevice>)desc.metal_device;
    } else {
        device = MTLCreateSystemDefaultDevice();
        if (!device) {
            errorf("Failed to get a Metal device");
            return false;
        }
    }

    if (desc.metal_command_queue) {
        queue = (__bridge id<MTLCommandQueue>)desc.metal_command_queue;
    } else {
        queue = [device newCommandQueue];
        if (!queue) {
            errorf("Failed to create a command queue");
            return false;
        }
    }

    return true;
}

bool metal_device::be_add_module(const module_desc &desc)
{
    if (desc.type == module_type::metal_source) {
        NSString* source = [[NSString alloc] initWithBytes:desc.data length:desc.size encoding:NSUTF8StringEncoding];
        NSError *error = nil;
        // TODO: Parse desc.opts
        id<MTLLibrary> lib = [device newLibraryWithSource:source options:nil error:&error];
        if (!lib) {
            errorf("%s: Failed to compile library (%s:%d):\n%s", desc.name,
                   [[error domain] UTF8String], [error code],
                   [[error localizedDescription] UTF8String]);
            return false;
        }
        libraries.push_back(lib);
    } else if(desc.type == module_type::metal_binary) {
        dispatch_data_t data = dispatch_data_create(desc.data, desc.size, nullptr, DISPATCH_DATA_DESTRUCTOR_DEFAULT);
        NSError *error = nil;
        id<MTLLibrary> lib = [device newLibraryWithData:data error:&error];
        if (!lib) {
            errorf("%s: Failed to load binary library (%s:%d):\n%s", desc.name,
                   [[error domain] UTF8String], [error code],
                   [[error localizedDescription] UTF8String]);
            return false;
        }
        libraries.push_back(lib);
    }
    return true;
}

buffer_base *metal_device::be_create_buffer(const buffer_desc &desc)
{
    return new metal_buffer(this, desc);
}

uintptr_t metal_device::be_find_kernel(const char *name)
{
    id<MTLFunction> func = nil;

    NSString *ns_name = [NSString stringWithUTF8String:name];
    for (const id<MTLLibrary> &lib : libraries) {
        func = [lib newFunctionWithName:ns_name];
        if (func) break;
    }

    if (!func) return 0;

    NSError *error = nil;
    id<MTLComputePipelineState> pipe = [device newComputePipelineStateWithFunction:func error:&error];
    if (!pipe) {
        errorf("%s: Failed to create compute pipeline (%s:%d): %s", name,
               [[error domain] UTF8String], [error code],
               [[error localizedDescription] UTF8String]);
        return 0;
    }

    pipelines.push_back(pipe);
    return (uintptr_t)pipelines.size();
}

bool metal_device::be_dispatch(const gp_uint3 &num_tiles, const be_dispatch_info &be_info, const dispatch_desc &desc, const dispatch_opts &opts)
{
    const kernel_info *info = desc.kernel;

    id<MTLComputeCommandEncoder> encoder = start_compute();
    id<MTLComputePipelineState> pipe = pipelines[be_info.kernel - 1];

    uint32_t ix_buffer = 0;
    uint32_t ix_shared = 0;

    [encoder setComputePipelineState:pipe];

    for (size_t i = 0; i < info->num_args; i++) {
        const arg_info &arg_info = info->args[i];
        arg_ptr arg = desc.args[i];
        switch (arg_info.type) {

            case arg_type::constant: {
                [encoder setBytes:(const void*)arg.data[0] length:arg_info.size atIndex:ix_buffer++];
            } break;

            case arg_type::buffer: {
                const metal_buffer *buf = (metal_buffer*)arg.data[0];
                [encoder setBuffer:buf->buffer offset:arg.data[1] atIndex:ix_buffer++];
            } break;

            case arg_type::shared_buffer: {
                uint32_t size_bytes = (uint32_t)arg.data[0];
                [encoder setThreadgroupMemoryLength:size_bytes atIndex:ix_shared++];
            } break;

        }
    }

    [encoder
        dispatchThreadgroups:MTLSizeMake(num_tiles.x, num_tiles.y, num_tiles.z)
        threadsPerThreadgroup:MTLSizeMake(info->tile_size[0], info->tile_size[1], info->tile_size[2])];

    return true;
}

bool metal_device::be_finish()
{
    if (!command_buffer) return true;
    end_encoding();

    @autoreleasepool {
        [command_buffer commit];
        [command_buffer waitUntilCompleted];
        NSError *error = [command_buffer error];
        if (error) {
            errorf("GPU error (%s:%d): %s",
                   [[error domain] UTF8String], [error code],
                   [[error localizedDescription] UTF8String]);
            return false;
        }
        command_buffer = nil;
    }

    return true;
}

void metal_device::end_encoding()
{
    @autoreleasepool {
        if (compute_encoder) {
            [compute_encoder endEncoding];
            compute_encoder = nil;
        }

        if (blit_encoder) {
            [blit_encoder endEncoding];
            blit_encoder = nil;
        }
    }
}

id<MTLCommandBuffer> metal_device::start_commands()
{
    end_encoding();

    if (!command_buffer) {
        command_buffer = [queue commandBuffer];
        if (!command_buffer) {
            errorf("Failed to create a command buffer");
        }
    }

    return command_buffer;
}

id<MTLComputeCommandEncoder> metal_device::start_compute()
{
    if (!compute_encoder) {
        id<MTLCommandBuffer> cmd = start_commands();
        if (cmd) {
            compute_encoder = [cmd computeCommandEncoder];
            if (!compute_encoder) {
                errorf("Failed to create a command encoder");
            }
        }
    }

    return compute_encoder;
}

id<MTLBlitCommandEncoder> metal_device::start_blit()
{
    if (!blit_encoder) {
        id<MTLCommandBuffer> cmd = start_commands();
        if (cmd) {
            blit_encoder = [cmd blitCommandEncoder];
            if (!blit_encoder) {
                errorf("Failed to create a command encoder");
            }
        }
    }
    return blit_encoder;
}

#endif

bool try_device(device &dev, const device_desc &desc, device_base *base)
{
    if (!base->init(desc)) {
        base->release();
        return false;
    }

    imp_set(dev, base);
    return true;
}

}

// -- API

const dispatch_opts dispatch_opts::defaults = { };

device create_device(const device_desc &desc)
{
    device dev;

#ifdef GP_USE_METAL
    if (desc.use_metal) {
        if (imp::try_device(dev, desc, new imp::metal_device())) {
            return dev;
        }
    }
#endif

#ifdef GP_USE_CUDA
    if (desc.use_cuda) {
        int count = 0;
        CUresult res = cuDeviceGetCount(&count);

        if (res == CUDA_ERROR_NOT_INITIALIZED) {
            res = cuInit(0);
            if (res == CUDA_SUCCESS) {
                res = cuDeviceGetCount(&count);
            }
        }

        if (res == CUDA_SUCCESS && count > 0) {
            if (imp::try_device(dev, desc, new imp::cuda_device())) {
                return dev;
            }
        }
    }
#endif

#ifdef GP_USE_OPENCL
    if (desc.use_opencl) {
        cl_uint count = 0;
        cl_int err = clGetPlatformIDs(0, nullptr, &count);
        if (err == CL_SUCCESS && count > 0) {
            if (imp::try_device(dev, desc, new imp::opencl_device())) {
                return dev;
            }
        }
    }
#endif

#ifndef GP_NO_CPU
    if (desc.use_cpu) {
        if (imp::try_device(dev, desc, new imp::cpu_device())) {
            return dev;
        }
    }
#endif

    imp::device_base *base = new imp::bad_device();
    base->errorf("Could not find a device");
    imp::imp_set(dev, base);
    return dev;
}

}

uint32_t gp_atomic_add(uint32_t &ref, uint32_t value)
{
    return ((std::atomic_uint32_t&)ref).fetch_add(value, std::memory_order_relaxed);
}

uint32_t gp_atomic_or(uint32_t &ref, uint32_t value)
{
    return ((std::atomic_uint32_t&)ref).fetch_or(value, std::memory_order_relaxed);
}

uint32_t gp_atomic_xchg(uint32_t &ref, uint32_t value)
{
    return ((std::atomic_uint32_t&)ref).exchange(value, std::memory_order_relaxed);
}


#endif
#endif