from   conan import ConanFile
from   conan.tools.build import can_run
from   conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
import os


class RohdeSchwarzTestPackageConan(ConanFile):
    settings      = "os", "compiler", "build_type", "arch"
    generators    = 'CMakeDeps', 'CMakeToolchain'
    tool_requires = 'cmake/[>=3.27 <4.0]'


    requires = 'rohdeschwarz/[>=0.1 <1.0]'


    def layout(self):
        cmake_layout(self)


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def test(self):
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "main")
            self.run(cmd, env="conanrun")
