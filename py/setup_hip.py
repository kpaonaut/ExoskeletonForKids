from distutils.core import setup, Extension

extension_mod = Extension("_hip", ["../hip.cpp", "build/hip_py_wrapper.cxx"],extra_compile_args=['-std=c++11','-stdlib=libc++','-Wno-c++11-extensions'])

setup(name = "hip", ext_modules=[extension_mod])