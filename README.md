# rohdeschwarz (C++) ![Static Release Build Badge](https://github.com/Terrabits/rohdeschwarz-cpp/actions/workflows/build-static-release.yml/badge.svg) ![Static Debug Build Badge](https://github.com/Terrabits/rohdeschwarz-cpp/actions/workflows/build-static-debug.yml/badge.svg) ![Shared Release Build Badge](https://github.com/Terrabits/rohdeschwarz-cpp/actions/workflows/build-shared-release.yml/badge.svg) ![Shared Debug Build Badge](https://github.com/Terrabits/rohdeschwarz-cpp/actions/workflows/build-shared-debug.yml/badge.svg)


An object-oriented test automation library for Rohde & Schwarz (R&S) General Purpose Test and Measurement (T&M) equipment.

## Requirements

-   [Conan](https://conan.io) ~= 2.0
-   [A Boost-compatible compiler](https://www.boost.org/development/tests/develop/developer/summary.html)\*

\*See the [Boost OS and Compiler Regression Testing Result Tables](https://www.boost.org/development/tests/develop/developer/summary.html) for a list of known-good compilers and versions for the latest version of Boost.

## Build

The following conan commands build a `static` `Release` version of this package:

```shell
cd path/to/rohdeschwarz
conan install . --update --build missing
conan build .
```

For convenience, the scripts [scripts/install](scripts/install)[.bat](scripts/install.bat) and [scripts/build](scripts/build)[.bat](scripts/build.bat) are also provided.

### Shared, Debug Builds

A static release build is the default. The following conan flags can be used with `conan install` and `conan build` to build other binaries:

-   `--settings build_type=Debug`
-   `--options */*:shared=True`

For example, to build a `shared` `Debug` binary:


```shell
# flags
SHARED="--options */*:shared=True"
DEBUG="--settings build_type=Debug"

# build shared debug
scripts/install $SHARED $DEBUG
scripts/build   $SHARED $DEBUG
```

## rohdeschwarz Library

The `rohdeschwarz` library is comprised of the following `namespaces` based on their functionality.

### busses

The `rohdeschwarz::busses` namespace contains instrument I/O libraries.

See [include/rohdeschwarz/busses/README.md](include/rohdeschwarz/busses/README.md) for more information.

## Examples

Basic examples for various parts of the `rohdeschwarz` library are provided in the [examples/](examples/) folder.

See [examples/README.md](examples/README.md) for more information.
