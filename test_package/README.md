# Test Package

The conan test package for `rohdeschwarz`.

## Description

A socket is created with host `localhost` and port `5025`. On success, the instrument `id` is queried (scpi: `*IDN?`). Exceptions of type `rohdeschwarz::busses::socket::system_error` are caught, with no further action.

## Return Code

The application should always return `0`; anything else is considered a problem with the package.

## Source

See [src/main.cpp](src/main.cpp) for test package source code.
