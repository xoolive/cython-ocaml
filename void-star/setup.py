from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extensions = [Extension("pywrapper",
                        ["pywrapper.pyx", "wrapper.cpp"],
                        language="c++")
              ]

setup(ext_modules=cythonize(extensions))
