from distutils.core import setup, Extension

extension_mod = Extension("_knee", ["../knee.cpp", "build/knee_py_wrapper.cxx"],extra_compile_args=['-std=c++11','-stdlib=libc++','-Wno-c++11-extensions'])

setup(name = "knee", ext_modules=[extension_mod])