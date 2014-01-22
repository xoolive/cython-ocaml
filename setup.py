from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extensions = [Extension("pywrapper",
                        ["pywrapper.pyx",
                         "wrapper.cpp"],
                        language="c++"),
              ]

setup(name="sample",
      version="0.1",
      author="Xavier Olive",
      author_email="xavier.olive@onera.fr",
      description="Sample project",
      ext_modules=cythonize(extensions),
      packages=["sample"])
