# rohdeschwarz (C++)

A C++ TCPIP socket library for Rohde & Schwarz (R&S) instrument control

## Build Requirements

-   [CMake](https::/cmake.org) ~= 3.20
-   [Conan](https://conan.io) ~= 2.0
-   [A Boost-compatible compiler](https://www.boost.org/development/tests/develop/developer/summary.html)\*

\*See the [Boost OS and Compiler Regression Testing Result Tables](https://www.boost.org/development/tests/develop/developer/summary.html) for a list of known-good compilers and versions for the latest version of Boost.

### Conan Extension for Visual Studio

The [Conan Extension for Visual Studio](https://marketplace.visualstudio.com/items?itemName=conan-io.conan-vs-extension&ssr=false#review-details) is required to build this project in Visual Studio, as conan is required.

## Build

Build scripts can be found in the [scripts](./scripts) folder.

## Examples

### rohdeschwarz::busses::Socket

See [examples/socket.cpp](examples/socket.cpp) for a TCPIP sockets example.
