import pcpp
import argparse
import subprocess
import os
import sys
import shutil
from collections import namedtuple
from itertools import chain
import re
import string
import platform

is_windows = platform.system() == "Windows"
is_apple = platform.system() == "Darwin"

opencl_cc_source = """
#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__)
    #include <OpenCL/cl.h>
#else
    #include <CL/cl.h>
#endif

int main(int argc, char **argv)
{
    char *file_data = NULL, *err_data = NULL;
    size_t file_len = 0, err_len = 0;
    cl_int err = 0;
    cl_uint num_pts, pt, num_devs, dev;
    cl_platform_id *pts = NULL;
    cl_device_id *devs = NULL;
    cl_context ctx = NULL;
    cl_program prg = NULL;
    cl_context_properties props[4] = { CL_CONTEXT_PLATFORM };
    int ok = 1;
    int status = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: opencl_cc [file]\\n");
        return 1;
    }

    {
        const char *filename = argv[1];
        FILE *file = fopen(filename, "rb");
        ok = ok && file != NULL;
        ok = ok && !fseek(file, 0, SEEK_END);
        file_len = ftell(file);
        ok = ok && !fseek(file, 0, SEEK_SET);
        ok = ok && (file_data = malloc(file_len)) != NULL;
        ok = ok && (fread(file_data, 1, file_len, file) == file_len);
        ok = ok && !fclose(file);
        if (!ok) {
            fprintf(stderr, "Failed to read input file: %s\\n", filename);
            return 2;
        }
    }

    ok = ok && !clGetPlatformIDs(0, NULL, &num_pts);
    ok = ok && (pts = calloc(num_pts, sizeof(cl_platform_id))) != NULL;
    ok = ok && !clGetPlatformIDs(num_pts, pts, NULL);

    for (pt = 0; pt < num_pts; pt++) {
        ok = ok && !clGetDeviceIDs(pts[pt], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devs);
        ok = ok && (devs = calloc(num_pts, sizeof(cl_device_id))) != NULL;
        ok = ok && !clGetDeviceIDs(pts[pt], CL_DEVICE_TYPE_ALL, num_devs, devs, NULL);
        props[1] = (cl_context_properties)pts[pt];

        for (dev = 0; dev < num_devs; dev++) {
            ok = ok && (ctx = clCreateContext(props, 1, &devs[dev], NULL, NULL, NULL)) != NULL;
            ok = ok && (prg = clCreateProgramWithSource(ctx, 1, (const char**)&file_data, &file_len, NULL)) != NULL;

            if (ok) {
                err = clBuildProgram(prg, 1, &devs[dev], "", NULL, NULL);
                if (err == CL_BUILD_PROGRAM_FAILURE) {
                    ok = ok && !clGetProgramBuildInfo(prg, devs[dev], CL_PROGRAM_BUILD_LOG, 0, NULL, &err_len);
                    ok = ok && (err_data = calloc(1, err_len + 1)) != NULL;
                    ok = ok && !clGetProgramBuildInfo(prg, devs[dev], CL_PROGRAM_BUILD_LOG, err_len, err_data, NULL);
                    if (ok) {
                        fprintf(stderr, "%s\\n", err_data);
                        status = 3;
                    }
                    if (err_data) { free(err_data); err_data = NULL; }
                }
            }

            if (prg) { clReleaseProgram(prg); prg = NULL; }
            if (ctx) { clReleaseContext(ctx); ctx = NULL; }
        }

        if (devs) { free(devs); devs = NULL; }
    }

    if (!ok) {
        fprintf(stderr, "Warning: Could not compile due to OpenCL API errors\\n");
    }

    return status;
}
"""

class GpccPreprocessor(pcpp.Preprocessor):
    def __init__(self, defines):
        super(GpccPreprocessor, self).__init__()
        
        # Override Preprocessor instance variables
        self.define("__PCPP_ALWAYS_FALSE__ 0")
        self.define("__PCPP_ALWAYS_TRUE__ 1")
        self.compress = 0

        if is_apple:
            self.define("GP_APPLE 1")
        else:
            self.define("GP_APPLE 0")

        self.pragmas = []

        for d in defines:
            self.define(d[0] + " " + d[1])

    def on_directive_unknown(self,directive,toks,ifpassthru,precedingtoks):
        if directive.value == "pragma":
            pragma = tuple(t.value for t in toks if t.type != "CPP_WS")
            if pragma and pragma[0] == "gpcc":
                self.pragmas.append(pragma[1:])
        return super(GpccPreprocessor, self).on_directive_unknown(directive,toks,ifpassthru,precedingtoks)

ichain = chain.from_iterable

parser = argparse.ArgumentParser(
    description="Compile compute kernels")

parser.add_argument("file", nargs="+",
    help="input files to process")

parser.add_argument("-o", metavar="output", nargs="?",
    help="output .c file")

parser.add_argument("-t", metavar="type", action="append",
    help="module types to process, matches gp::module_type")

parser.add_argument("-D", metavar="define", action="append",
    default=[], help="defines to pass to preprocessor")

parser.add_argument("--temp-dir", default="gpcc_temp",
    help="temporary directory")

argv = parser.parse_args()

tmp_path = argv.temp_dir

os.makedirs(tmp_path, exist_ok=True)

def copy_file(src, dst):
    print(f"$ cp {src} {dst}", file=sys.stderr)
    shutil.copyfile(src, dst)

def run_exe(tool, args):
    exe_args = [tool] + args
    print(f"$ " + " ".join(exe_args), file=sys.stderr)
    subprocess.check_call(exe_args)

def preprocess(src, dst, defines=[]):
    args = ["pcpp", src, "-o", dst]
    for d in defines:
        args += "-D", d
    print(f"$ " + " ".join(args), file=sys.stderr)
    p = pcpp.CmdPreprocessor(args)
    if p.return_code != 0:
        raise RuntimeError(f"pcpp failed with {p.return_code}")

Output = namedtuple("Output", "src_path dst_path name module_type")

def path_to_ident(path, namespace):
    base = os.path.basename(path)
    dot_ix = base.find(".")
    if dot_ix > 0:
        base = base[:dot_ix]
    base = re.sub(r"[^A-Za-z0-9]", "_", base)
    if base and base[0] in string.digits:
        base = "_" + base
    if len(base) > 64: base = base[:64]
    if not base:
        base = "gpcc_name"

    ix = 0
    name = base
    while name in namespace:
        name = base + str(ix)
        ix += 1
    namespace.add(name)
    return name

in_names = set()

def setup_opencl_checker(exe_path):
    if not os.path.isfile(exe_path) or os.path.getmtime(exe_path) < os.path.getmtime(__file__):
        print(f"-- Compiling {os.path.basename(exe_path)}", file=sys.stderr)
        source_path = os.path.join(tmp_path, "opencl_cc.c")
        with open(source_path, "w") as f:
            f.write(opencl_cc_source)

        if is_windows:
            obj_path = os.path.abspath(tmp_path).replace("\\", "\\\\")
            args = [source_path, "/nologo"]
            args += ["/I", os.path.join(os.getenv("CUDA_PATH"), "include")]
            args += [f"/Fo{obj_path}\\opencl_cc.obj"]
            args += ["/link"]
            args += ["/LIBPATH:" + os.path.join(os.getenv("CUDA_PATH"), "lib", "x64")]
            args += ["opencl.lib"]
            args += ["/OUT:" + exe_path]
            try:
                run_exe("cl", args)
            except:
                return False
        else:
            args = [source_path]
            if is_apple:
                args += ["-framework", "OpenCL"]
            else:
                args += ["-lOpenCL"]
            args += ["-o", exe_path]
            try:
                run_exe("cc", args)
            except:
                return False

    return True

def check_opencl(src_path):
    exe_path = os.path.join(tmp_path, "opencl_cc.exe" if is_windows else "opencl_cc")
    if setup_opencl_checker(exe_path):
        run_exe(exe_path, [src_path])

def unixify_file(path):
    """Normalize line endings to LF only and convert #line directive backslashes"""
    with open(path) as f:
        lines = f.readlines()
    with open(path, "wb") as f:
        for line in lines:
            line = line.rstrip("\r\n")
            if line.strip().startswith("#line"):
                line = line.replace("\\", "/")
            line += "\n"
            f.write(line.encode("utf-8"))

class File:
    def __init__(self, src_path):
        self.src_path = src_path
        self.src_original_name = name = path_to_ident(src_path, in_names)
        self.src_name = name

        self.tmp_path = tmp_path
        self.outputs = []
        self.failed = False
    
    def tmp_file(self, name):
        return os.path.join(self.tmp_path, name)

    def opencl_source(self):
        out_path = self.tmp_file(self.src_name + ".cl")
        preprocess(self.src_path, out_path,
            defines=["GP_OPENCL_SOURCE"],
        )

        unixify_file(out_path)
        check_opencl(out_path)

        return out_path

    def metal_source(self):
        out_path = self.tmp_file(self.src_name + ".metal")
        preprocess(self.src_path, out_path,
            defines=["GP_METAL_SOURCE"],
        )

        unixify_file(out_path)

        return out_path

    def metal_binary(self):
        air_path = self.tmp_file(self.src_name + ".air")
        out_path = self.tmp_file(self.src_name + ".metallib")

        args = ["-sdk", "macosx", "metal"]
        args += ["-x", "metal", "-c", self.src_path, "-o", air_path]
        run_exe("xcrun", args)

        args = ["-sdk", "macosx", "metallib"]
        args += [air_path, "-o", out_path]
        run_exe("xcrun", args)

        return out_path

    def cuda_binary(self):
        out_path = self.tmp_file(self.src_name + ".ptx")

        args = [self.src_path, "-x", "cu", "--ptx", "-o", out_path]
        run_exe("nvcc", args)

        unixify_file(out_path)

        return out_path

    def process(self, module_type):
        func = getattr(self, module_type, None)
        if not func:
            raise ValueError(f"Bad module_type: {module_type}")
        try:
            dst_path = func()
            o = Output(self.src_path, dst_path, self.src_name, module_type)
            self.outputs.append(o)
        except subprocess.CalledProcessError:
            self.failed = True
            print(f"-- Failed: {module_type} {self.src_path}", file=sys.stderr)

files = [File(f) for f in argv.file]

module_types = set(argv.t) if argv.t else set()

class NullStream(object):
    def write(self, *args): pass

for f in files:
    defines = [
        ("GPCC_CONFIG", "1"),
        ("GP_INCLUDED", "1"),
        ("GP_IMPLEMENTED", "1"),
    ]

    for d in argv.D:
        if "=" in d:
            name, val = d.split("=", 1)
            defines.append((name, val))
        else:
            defines.append((d, "1"))

    pp = GpccPreprocessor(defines)
    with open(f.src_path) as of:
        pp.parse(of)
        pp.write(NullStream())
    for pragma, *args in pp.pragmas:
        if pragma == "type":
            module_types |= set(args)
        else:
            raise ValueError(f"Unknown #pragma gpcc {pragma}")
        

for src_file in files:
    for module_type in sorted(module_types):
        print(f"-- {module_type} {src_file.src_path}", file=sys.stderr)
        src_file.process(module_type)

for f in files:
    if f.failed:
        exit(1)

outputs = list(ichain(f.outputs for f in files))

str_lit_set = set(range(32, 127))
str_lit_set |= set("\r\n\t")

def fmt_byte(b):
    if b == ord("\""): return "\\\""
    elif b == ord("\\"): return "\\\\"
    elif b == ord("\t"): return "\t"
    elif b == ord("\n"): return "\\n"
    elif b == ord("\r"): return "\\r"
    elif b >= 32 and b <= 127: return chr(b)
    else:
        return f"\\x{b:02x}"

wrap_column = 100

def format_output(outputs, out_base):

    result = bytearray()
    byte_to_str = [f"0x{b:02x},".encode("utf-8") for b in range(256)]

    result.extend(b"// Generated by guppy_cc.py, do not modify!\n\n")

    for o in outputs:
        with open(o.dst_path, "rb") as f:
            data = f.read()
        
        result.extend(f"static const unsigned char gpcc_{o.name}_{o.module_type}[] = {{\n".encode("utf-8"))

        lit_prefix = b""
        lit_suffix = b"\n"
        lit_sep = lit_suffix + lit_prefix

        prefix_len = len(lit_prefix)
        line_len = prefix_len

        wrap_len = wrap_column - (len(lit_sep) - 1)
        ord_n = ord("\n")

        result.extend(lit_prefix)

        begin = 0
        end = len(data)
        ix = 0
        while ix < end:
            bt = data[ix]
            cs = byte_to_str[bt]
            cl = len(cs)

            result.extend(cs)
            line_len += cl

            if line_len >= wrap_len:
                result.extend(lit_sep)
                line_len = prefix_len

            ix += 1

        result.extend(b"0x00\n};\n\n")
    
    result.extend(b"#if defined(__cplusplus) && defined(GP_INCLUDED)\n")
    result.extend(f"static constexpr size_t gpcc_{out_base}_count = {len(outputs)};\n".encode("utf-8"))
    result.extend(f"static const ::gp::module_desc gpcc_{out_base}[] = {{\n".encode("utf-8"))
    for o in outputs:
        name = f"gpcc_{o.name}_{o.module_type}"
        base = os.path.basename(o.src_path).replace("\\", "/")
        result.extend(f"\t{{ ::gp::module_type::{o.module_type}, {name}, sizeof({name}) - 1, \"{base}\" }},\n".encode("utf-8"))
    result.extend(b"};\n")
    result.extend(b"#endif\n")
    result.extend(b"\n")

    return result

out_path = argv.o
if not out_path:
    out_path = files[0].src_path + ".h"

out_base = path_to_ident(out_path, set())
result = format_output(outputs, out_base)
with open(out_path, "wb") as f:
    f.write(result)
