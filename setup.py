from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os, subprocess, sys


class CmakeExtension(Extension):
    def __init__(self, name, cmake_lists_dir='.', **kwa):
        super().__init__(name, sources=[], **kwa)
        self.cmake_lists_dir = os.path.abspath(cmake_lists_dir)

class CmakeBuild(build_ext):
    def build_extensions(self):
        try:
            subprocess.check_call(['cmake', '--version'])
        except subprocess.CalledProcessError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        for ext in self.extensions:
            extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

            cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                            '-DPYTHON_EXECUTABLE=' + sys.executable]

            if not os.path.exists(self.build_temp):
                os.makedirs(self.build_temp)

            subprocess.check_call(['cmake', ext.cmake_lists_dir] + cmake_args, cwd=self.build_temp)

            subprocess.check_call(['cmake', '--build', '.'], cwd=self.build_temp)

setup(
    name="HelloModule",
    version="1.0",
    ext_modules=[CmakeExtension("HelloModule")],
    cmdclass = {'build_ext': CmakeBuild},
)