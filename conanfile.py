from conan             import ConanFile
from conan.errors      import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, cmake_layout


class RohdeSchwarzConan(ConanFile):

    # basic info
    name    = "rohdeschwarz"
    version = "0.2.0"
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
        self.requires('boost/[>=1.83 <2]', transitive_headers=True, transitive_libs=True)


    # build tools
    tool_requires = 'cmake/[>=3.27 <4.0]'


    # build configuration
    package_type  = 'library'
    settings      = "os", "compiler", "build_type", "arch"


    # options
    options = {
        "shared": [True, False],
        "fPIC":   [True, False]
    }

    # default options
    default_options = {
        "shared": False,
        "fPIC":   True,
    }


    # sources
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


    # delete fpic option on windows
    implements = ['auto_shared_fpic']


    def validate(self):
        # requires c++ std 17  or greater
        check_min_cppstd(self, '17')

        # requires boost::filesystem
        if self.dependencies["boost"].options.without_filesystem:
            raise ConanInvalidConfiguration('boost option without_filesystem must be False; boost::filesystem is required')

        # requires boost::system
        if self.dependencies["boost"].options.without_system:
            raise ConanInvalidConfiguration('boost option without_system must be False; boost::system is required')


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
