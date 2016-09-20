import sys
import numpy
import os
from numpy.distutils.core import setup, Extension

if sys.version_info[0] == 3:

    include = os.path.join(os.getcwd(),'include')

    module = Extension('operations',
                       language = "c++",
                       sources = ['operations.cpp'],
                       extra_compile_args = ['-O3 -std=c++11 -fopenmp -Wall'],
                       extra_link_args = ['-lgomp'], 
                       include_dirs = [include,numpy.get_include()] )

    setup(name = 'operations',
          author = 'Greg von Winckel',
          author_email = 'gregvw@gmail.com',
          ext_modules = [module])

else:
    print("This project requires building with Python 3")
