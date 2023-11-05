@rem Build the example on Windows with the CUDA Toolkit
@rem The toolkit includes both CUDA and OpenCL.

@rem Check that cl.exe is available
where cl.exe /q
@ if errorlevel 1 (
    @echo Error: cl.exe not found, run this .bat from an MSVC tools command
    @echo   prompt or run the correct vcvarsall.bat beforehand.
    exit 1
)

@rem Create a build directory
mkdir build

@rem Compile options:
@rem   /I "%CUDA_PATH%\include"  CUDA include path (includes OpenCL)
@rem   /Fobuild\                 Emit .obj files to build\
@rem   /EHsc                     Enable exception handling support for C++
set CL_OPTS=/I "%CUDA_PATH%\include" /Fobuild\ /EHsc

@rem Link options:
@rem   /LIBPATH:"%CUDA_PATH%\lib\x64"  CUDA library path (includes OpenCL)
@rem   opencl.lib                      Additional libraries (OpenCL)
set LINK_OPTS=/LIBPATH:"%CUDA_PATH%\lib\x64" opencl.lib

@rem Compile the executable to build\example.exe
cl.exe %CL_OPTS% main.cpp /link %LINK_OPTS% /OUT:build\example.exe
