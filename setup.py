#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Boost Python Bullet
=======
This is the setup file for the boost python thin wrapper for the
Bullet Physics SDK (see: http://bulletphysics.org/)
"""
import os
from setuptools import find_packages
from distutils.core import setup, Extension


def parallelCCompile(self, sources, output_dir=None, macros=None,
                     include_dirs=None, debug=0, extra_preargs=None,
                     extra_postargs=None, depends=None):
    '''Hack for parallel compilation in distutils'''
    # those lines are copied from distutils.ccompiler.CCompiler directly
    macros, objects, extra_postargs, pp_opts, build = \
        self._setup_compile(output_dir, macros, include_dirs, sources, depends,
                            extra_postargs)
    cc_args = self._get_cc_args(pp_opts, debug, extra_preargs)
    # parallel code
    N = 8  # number of parallel compilations
    import multiprocessing.pool

    def _single_compile(obj):
        try:
            src, ext = build[obj]
        except KeyError:
            return
        self._compile(obj, src, ext, cc_args, extra_postargs, pp_opts)
    # convert to list, imap is evaluated on-demand
    list(multiprocessing.pool.ThreadPool(N).imap(_single_compile, objects))
    return objects
import distutils.ccompiler
distutils.ccompiler.CCompiler.compile = parallelCCompile

requires = []


def list_cpp(d, skips=[]):
    p = os.path.abspath(d)
    for root, _, files in os.walk(d):
        for f in [_f for _f in files if _f.endswith('.cpp')]:
            yield '%s/%s' % (root, f)


def find_sources(dirs):
    for d in dirs:
        for f in list_cpp(d):
            yield f

src_dirs = (
    'bullet/src/boost',
    'bullet/src/LinearMath',
)

macros = [
    ('BT_USE_DOUBLE_PRECISION', '1'),
]


modules = [
    Extension(str('bullet'),  # hack for distutils string param in Extension
              sources=[s for s in find_sources(src_dirs)],
              define_macros=macros,
              libraries=['boost_python'],
              include_dirs=['bullet/src'])
]

setup(
    name='boost_python_bullet',
    version='0.1.0',
    packages=find_packages(),
    author="Högni Gylfason",
    author_email="klumhru@gmail.com",
    install_requires=requires,
    description=__doc__,
    include_package_data=True,
    classifiers=[
        "Development Status :: 5 - Alpha",
        "Intended Audience :: Developers",
        "Licence :: MIT",
        "Operating System :: OS Independent",
        "Programming Language :: Python",
    ],
    zip_safe=True,
    ext_modules=modules,
)
