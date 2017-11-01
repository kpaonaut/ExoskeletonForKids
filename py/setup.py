from distutils.core import setup, Extension

extension_mod = Extension("_trajectory_template", ["../trajectory_template.cpp","build/trajectory_template_py_wrap.cxx"],extra_compile_args=['-std=c++11','-stdlib=libc++','-Wno-c++11-extensions'])

setup(name = "trajectory_template", ext_modules=[extension_mod])