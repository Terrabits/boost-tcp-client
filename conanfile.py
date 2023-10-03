from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class RohdeSchwarzConan(ConanFile):

    # basic info
    name    = "rohdeschwarz"
    version = "0.1.0"
    license = "R&S Royalty Free License"
    author  = "Nick Lalic <nick.lalic@rsa.rohde-schwarz.com"
    url     = "https://github.com/Terrabits/boost-tcp-client"
    description = (
        "An object-oriented library for automation of Rohde & Schwarz general "
        "purpose test and measurement equipment"
    )
    topics  = (
        "Rohde",
        "Schwarz",
        "R&S",
        "Test",
        "Measurement",
        "Instrument",
        "Automation"
    )


    # requirements
    requires      = 'boost/[>=1.83 <2.0]'
    tool_requires = 'cmake/[>=3.27 <4.0]'


    # build configuration, options
    package_type  = 'library'
    settings      = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC":   [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC":   True
    }


    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC


    def layout(self):
        cmake_layout(self)


    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()


    def package_info(self):
        self.cpp_info.libs = ["rohdeschwarz"]
