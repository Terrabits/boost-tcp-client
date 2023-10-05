# Socket

The `rohdeschwarz::busses::socket` namespace uses TCPIP for instrument I/O.

## Header

```cpp
#include "rohdeschwarz/busses/socket/socket.hpp"

// optional
using namespace rohdeschwarz::busses::socket;
using Socket =  rohdeschwarz::busses::socket::Socket;
```

## Basic Use

Basic use is as follows:

```cpp
// create open socket
Socket socket(HOST, PORT);

// print instrument id string
std::cout << socket.query("*IDN?\n");
```

See [examples/socket/README.md](examples/socket/README.md) for a complete basic sockets example.

## References

| class                                        | header        |
| -------------------------------------------- | ------------- |
| `rohdeschwarz::busses::socket::Address`      | `address.hpp` |
| `rohdeschwarz::busses::socket::Buffer`       | `buffer.hpp`  |
| `rohdeschwarz::busses::socket::Socket`       | `socket.hpp`  |
| `rohdeschwarz::busses::socket::system_error` | `socket.hpp`  |
