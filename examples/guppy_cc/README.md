
Prereqiusites:

- Python 3.6 or newer
- PyPi package `pcpp` (`pip3 install pcpp`)
- CUDA on Windows
- CUDA/OpenCL on Linux
- Xcode on macOS

## guppy_cc.py

`guppy_cc.py` compiles/validates kernels to be used with Guppy. It produces a
header with the kernels that can be included into the final executable.

In the most minimal configuration you only need to call `guppy_cc.py kernels.gpcc`
which will generate the resulting header `kernels.gpcc.h` next to the input file.
You should declare platforms you want to compile using  `#pragma gpcc type`
statement and include the kernel file(s) you want to compile.

```c
#pragma gpcc type opencl_source
#include "kernels.h"
```

You can include different options for different platforms using the preprocessor:

```c
#if GP_APPLE
    #pragma gpcc type metal_binary opencl_source
#else
    #pragma gpcc type cuda_binary opencl_source
#endif

#include "kernels.h"
```

### Using the generated header

The generated `.gpcc.h` header has `static` arrays containing the compiled kernels
so you should include it only in as single file. The header will define an array
of `gp::module_desc` values that you can pass to `gp::create_device()`. The
declarations look something like the following for `my_kernels.gpcc`:

```cpp
static constexpr size_t gpcc_my_kernels_count = 2;
static const ::gp::module_desc gpcc_my_kernels[] = {
	{ ::gp::module_type::cuda_binary, gpcc_my_kernels_cuda_binary, sizeof(gpcc_my_kernels_cuda_binary) - 1, "my_kernels.gpcc" },
	{ ::gp::module_type::opencl_source, gpcc_my_kernels_opencl_source, sizeof(gpcc_my_kernels_opencl_source) - 1, "my_kernels.gpcc" },
};
```

## Building the example

### Windows (command line)

You need to have a terminal with `cl.exe` available, either a developer command
prompt or one with `vcvars64.bat` enabled.

- CUDA: `build_win_cuda.bat`
