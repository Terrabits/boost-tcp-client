from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class RohdeSchwarzConan(ConanFile):
    name    = "rohdeschwarz"
    version = "1.0.0"


    # Optional metadata
    license = "R&S Royalty Free License"
    author  = "Nick Lalic <nick.lalic@rsa.rohde-schwarz.com"
    url     = ""
    description = "Boost TCP Socket example for Rohde & Schwarz instrument control"
    topics  = ("Rohde", "Schwarz", "R&S", "Boost", "tcp", "socket")


    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options  = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}


    package_type = 'library'


    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*"


    def requirements(self):
        self.requires('boost/1.83.0')


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
