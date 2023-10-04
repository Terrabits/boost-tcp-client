from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class RohdeSchwarzTestPackageConan(ConanFile):
    requires      = 'rohdeschwarz/[>=0.1 <1.0]'
    tool_requires = 'cmake/[>=3.27 <4.0]'
    generators    = 'CMakeDeps', 'CMakeToolchain'
    settings      = "os", "compiler", "build_type", "arch"


    def layout(self):
        cmake_layout(self)


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
