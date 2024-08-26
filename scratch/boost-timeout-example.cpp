// Reference: How to set a timeout on blocking sockets in boost asio?
// https://stackoverflow.com/a/51850018/1390788
using const_char_p = const char*;
const int timeout_ms = 200;
::setsockopt(
  socket.native_handle(),
  SOL_SOCKET, SO_RCVTIMEO,
  const_char_p(&timeout_ms),
  sizeof timeout
); //SO_SNDTIMEO for send ops
