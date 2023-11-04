@rem Build the example on Windows.

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
@rem   /Fobuild\                 Emit .obj files to build\
@rem   /EHsc                     Enable exception handling support for C++
set CL_OPTS=/Fobuild\ /EHsc

@rem Compile the executable to build\example.exe
cl.exe %CL_OPTS% main.cpp /link /OUT:build\example.exe

