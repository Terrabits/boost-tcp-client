from conan             import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, cmake_layout


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


    # required libraries
    def requirements(self):
        self.requires('boost/1.83.0', transitive_headers=True, transitive_libs=True)


    # required build tools
    tool_requires = 'cmake/[>=3.27 <4.0]'


    # build configuration
    package_type  = 'library'
    settings      = "os", "compiler", "build_type", "arch"


    # build options
    options = {
        "shared": [True, False],
        "fPIC":   [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC":   True
    }


    # source files
    exports_sources = (
        'CMakeLists.txt',
        'conanfile.py',
        'LICENSE.txt',
        'README.md',
        'examples/*',
        'include/*',
        'src/*'
    )


    # cmake generators
    generators = "CMakeDeps", "CMakeToolchain"


    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")


    def validate(self):
        check_min_cppstd(self, '17')


    def layout(self):
        cmake_layout(self)


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()


    def package_info(self):
        self.cpp_info.libs = ["rohdeschwarz"]
