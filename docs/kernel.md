# Kernel dialect

## Predefined

```cpp
// Types uintN_t, intN_t are always supported.

// Aliases for basic types
typedef float gp_float;
typedef int32_t gp_int;
typedef uint32_t gp_uint;

// Vector types, these have operators oveloaded and can be constructed via eg.
// `gp_uint3(1, 2, 3)`
struct gp_float2 { gp_float x, y; };
struct gp_float3 { gp_float x, y, z; };
struct gp_float4 { gp_float x, y, z, w; };
struct gp_int2 { gp_int x, y; };
struct gp_int3 { gp_int x, y, z; };
struct gp_int4 { gp_int x, y, z, w; };
struct gp_uint2 { gp_uint x, y; };
struct gp_uint3 { gp_uint x, y, z; };
struct gp_uint4 { gp_uint x, y, z, w; };

// Language features
#define gp_func /* required for functions */
#define gp_kernel(name, x,y,z, args) /* kernel definition with (x,y,z) group */
#define gp_args(...) /* arguments used by the kernel, must be passed to args */

// Math wrappers
float gp_fabs(float a);
float gp_sqrt(float a);
float gp_min(float a, float b);
float gp_max(float a, float b);
float gp_sin(float a);
float gp_cos(float a);
bool gp_isnan(float a);

// Bit cast
gp_uint  gp_cast_uint (gp_int   v);
gp_uint2 gp_cast_uint2(gp_int2  v);
gp_uint3 gp_cast_uint3(gp_int3  v);
gp_uint4 gp_cast_uint4(gp_int4  v);
gp_int   gp_cast_int  (gp_uint  v);
gp_int2  gp_cast_int2 (gp_uint2 v);
gp_int3  gp_cast_int3 (gp_uint3 v);
gp_int4  gp_cast_int4 (gp_uint4 v);

// Comparison utility
bool gp_all_less_1d(gp_uint a, gp_uint b);
bool gp_all_less_2d(gp_uint2 a, gp_uint2 b);
bool gp_all_less_3d(gp_uint3 a, gp_uint3 b);
bool gp_all_less_4d(gp_uint4 a, gp_uint4 b);

// Control flow
#define gp_for_tile() { /* for each thread in group */ }
#define gp_once_per_tile_1d() { /* for thread (0) */ }
#define gp_once_per_tile_2d() { /* for thread (0,0) */ }
#define gp_once_per_tile_3d() { /* for thread (0,0,0) */ }
#define gp_for_tile_in_bounds_1d(bounds) { /* for thread (x) <= bounds */ }
#define gp_for_tile_in_bounds_2d(bounds) { /* for thread (x,y) <= bounds */ }
#define gp_for_tile_in_bounds_3d(bounds) { /* for thread (x,y,z) <= bounds */ }

// Argument types within gp_args()
#define gp_const(name)         /* constant value */
#define gp_buffer(name)        /* pointer */
#define gp_shared_buffer(type) /* dynamically sized group shared buffer */
#define gp_global_dim1         /* constant gp_uint that sets dispatch size */
#define gp_global_dim2         /* constant gp_uint2 that sets dispatch size */
#define gp_global_dim3         /* constant gp_uint3 that sets dispatch size */

// Thread indexing
#define gp_tile_size_1d() /* thread group size (x) */
#define gp_tile_size_2d() /* thread group size (x,y) */
#define gp_tile_size_3d() /* thread group size (x,y,z) */
#define gp_tile_index_1d() /* thread group index (x) */
#define gp_tile_index_2d() /* thread group index (x,y) */
#define gp_tile_index_3d() /* thread group index (x,y,z) */
#define gp_local_index_1d() /* thread local index (x) */
#define gp_local_index_2d() /* thread local index (x,y) */
#define gp_local_index_3d() /* thread local index (x,y,z) */
#define gp_global_index_1d() /* thread global index (x) */
#define gp_global_index_2d() /* thread global index (x,y) */
#define gp_global_index_3d() /* thread global index (x,y,z) */
#define gp_local_index_linear() /* linear index `(z*size_y + y)*size_x + x`

// Shared memory
#define gp_shared /* thread shared value */
#define gp_tile_sync_shared() /* group barrier flushing `gp_shared` memory */
#define gp_tile_sync_full()   /* group barrier flushing all memory */

// Atomic variables
typedef gp_atomic_uint;
#define gp_atomic_load(ref)         /* atomic load */
#define gp_atomic_store(ref, value) /* atomic store */
#define gp_atomic_add(ref, value)   /* atomic add returning old value */
#define gp_atomic_or(ref, value)    /* atomic or returning old value */
#define gp_atomic_xchg(ref, value)  /* atomic exchange returning old value */
```
