# guppy_cc.py

`guppy_cc.py` compiles/validates kernels to be used with Guppy. It produces a
header with the kernels that can be included into the final executable.

Supported platforms:

- Windows
  - OpenCL\*
  - CUDA
- Linux
  - OpenCL
  - CUDA
- macOS
  - OpenCL
  - Metal

  *\* Currently only supported with CUDA as `guppy_cc.py` can't detect other toolkits*

## Setup

Prerequisites:

- Python 3.6 or newer
- PyPi package `pcpp` (`pip3 install pcpp`)
- CUDA on Windows
- CUDA/OpenCL on Linux
- Xcode on macOS

## Usage

Use `guppy_cc.py` from the command line as follows, you can omit `--temp`
(defaults to `gpcc_temp`) and `-o` (defaults to adjacent `.gpcc.h` file).

```bash
python3 guppy_cc.py my_kernels.gpcc --temp temp -o build/my_kernels.gpcc.h
```

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

Ideally you should hook `guppy_cc.py` to a pre-build step in your preferred
build system.

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

```cpp
#include "guppy.h"
#include "my_kernels.h
#include "my_kernels.gpcc.h"

int main(int argc, char **argv)
{
    gp::device_desc desc;
    desc.modules = gpcc_my_kernels;
    desc.num_modules = gpcc_my_kernels_count;

    gp::device device = gp::create_device(desc);
    device.dispatch(my_kernel(...));
}
```

## Building the example

### Windows (command line)

See `build_win_*.bat` for details how to build this example. If you want to run
the `.bat` file make sure to have a command prompt with `cl.exe` in the path,
either via the MSVC developer command prompt or by running the correct `vcvarsall.bat`.

### Windows (Visual Studio)

See `project/guppy_cc_vs2019/` for a Windows example. Unfortunately it requires
CUDA to build it as Windows has no vendor-independent way of locating OpenCL.

The project builds `kernels.gpcc` as a pre-build step, you can see the details
from the GUI by opening the properties of `kernels.gpcc` in Solution Explorer
or the XML representation in the `.vcxproj`:

```xml
<CustomBuild Include="..\..\..\kernels.gpcc">
    <FileType>Document</FileType>
    <Command>python $(ProjectDir)..\..\..\..\..\guppy_cc.py %(FullPath) --temp-dir $(IntermediateOutputPath)\gpcc -o $(ProjectDir)..\..\..\build\kernels.gpcc.h</Command>
    <Message>guppy_cc.py</Message>
    <Outputs>$(ProjectDir)..\..\..\build\kernels.gpcc.h</Outputs>
    <AdditionalInputs>$(ProjectDir)..\..\..\kernels.h</AdditionalInputs>
</CustomBuild>
```

### macOS (command line)

See `build_mac_*.sh` for details how to build the example.

### Linux (command line)

See `build_linux_*.sh` for details how to build the example.

