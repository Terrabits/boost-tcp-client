# Socket Example

This project is an example for using the class `rohdeschwarz::busses::socket::Socket` for TCPIP control of a Rohde & Schwarz (R&S) instrument.

## Requirements

-   [Conan](https://conan.io) ~= 2.0
-   [A Boost-compatible compiler](https://www.boost.org/development/tests/develop/developer/summary.html)\*

\*See the [Boost OS and Compiler Regression Testing Result Tables](https://www.boost.org/development/tests/develop/developer/summary.html) for a list of known-good compilers and versions for the latest version of Boost.

## Build

The following conan commands build a `static` `Release` version of this package:

```shell
cd path/to/rohdeschwarz/examples/socket
conan install . --update --build missing
conan build .
```

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

## Source Code

See `src/main.cpp` for example source code
