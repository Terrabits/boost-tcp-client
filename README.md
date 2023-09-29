# Boost TCP Client

A TCP socket example for Rohde & Schwarz (R&S) instrument control.

## Requirements

-   [CMake](https::/cmake.org) ~= 3.20
-   [Conan](https://conan.io) ~= 2.0
-   [A compatible compiler](https://www.boost.org/development/tests/develop/developer/summary.html)\*

\*See the [Boost OS and Compiler Regression Testing Result Tables](https://www.boost.org/development/tests/develop/developer/summary.html) for a list of known-good compilers and versions for the latest version of Boost.

### Conan Extension for Visual Studio

The [Conan Extension for Visual Studio](https://marketplace.visualstudio.com/items?itemName=conan-io.conan-vs-extension&ssr=false#review-details) is required to build this project in Visual Studio, as conan is required.

## Build

Build scripts can be found in the [scripts](scripts) folder.

### Clean

[scripts/clean](scripts/clean) removes the `build` folder, which removes references to packages install by conan as well as all build artifacts.

### Static Release

The scripts [scripts/install](scripts/install) and [scripts/build](scripts/build) will build statically-linked release binaries by default.

### Shared

The scripts in the [scripts/shared](scripts/shared) folder can be used to build shared binaries.

### Debug

The scripts in the [scripts/debug](scripts/debug) and [scripts/shared/debug](scripts/shared/debug) folders can be used to build debug binaries with dynamically linked and statically linked binaries, respectively.
