/**
 * \file  socket.cpp
 * \brief rohdeschwarz::busses::socket::busses::socket::Socket class implementation
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/helpers.hpp"
#include "rohdeschwarz/busses/socket/socket.hpp"
using namespace rohdeschwarz::busses::socket;


// boost
const auto shutdown_both = boost::asio::ip::tcp::socket::shutdown_both;


// std lib
#include <sstream>


// types
// Note: do I need WS2tcpip.h on windows?
// See https://stackoverflow.com/a/4454036/1390788
using char_p       = char*;
using const_char_p = const char*;
using socklen_t_p  = socklen_t*;


Socket::Socket(const char* host, int port) :
  _host(host),
  _port(port),
  _socket(_io_context),
  _native_handle(_socket.native_handle())
{
  open();
}


Socket::Socket(const std::string& host, int port) :
  _host(host),
  _port(port),
  _socket(_io_context),
  _native_handle(_socket.native_handle())
{
  open();
}


Socket::~Socket()
{
  close();
}


std::string Socket::host() const
{
  return _host;
}


int Socket::port() const
{
  return _port;
}


std::string Socket::endpoint() const
{
  std::stringstream stream;
  stream << host() << ":" << port();
  return stream.str();
}


int Socket::timeout_ms() const
{
  // use read timeout
  int timeout_ms;
  int bytes_read;
  getsockopt(
    _native_handle,
    SOL_SOCKET, SO_RCVTIMEO,
    char_p(&timeout_ms),
    socklen_t_p(&bytes_read)
  );
  return timeout_ms;
}


bool Socket::setTimeout(int timeout_ms)
{
  // set read timeout
  int result = setsockopt
  (
      _native_handle,
      SOL_SOCKET, SO_RCVTIMEO,
      const_char_p(&timeout_ms),
      sizeof(timeout_ms)
  );
  if (result != 0)
  {
    // error
    return false;
  }

  // set write timeout
  result = setsockopt(
    _native_handle,
    SOL_SOCKET, SO_SNDTIMEO,
    const_char_p(&timeout_ms),
    sizeof(timeout_ms)
  );

  // success?
  return result == 0;
}


bool Socket::readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize)
{
  // read
  boost::asio::mutable_buffer _buffer
    = boost::asio::buffer(char_p(buffer), bufferSize);
  std::size_t _readSize;
  try
  {
    _readSize = boost::asio::read(_socket, _buffer);
  }

  // error?
  catch (const system_error& error)
  {
    return false;
  }

  // return read size?
  if (readSize != nullptr)
  {
    *readSize = _readSize;
  }

  // success
  return true;
}


bool Socket::writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize)
{
  // write
  boost::asio::const_buffer _buffer
    = boost::asio::buffer(const_char_p(data), dataSize);
  std::size_t _writeSize;
  try
  {
    _writeSize = boost::asio::write(_socket, _buffer);
  }

  // error?
  catch (const system_error& error)
  {
    return false;
  }

  // return write size?
  if (writeSize != nullptr)
  {
    *writeSize = _writeSize;
  }

  // success
  return true;
}


bool Socket::isError() const
{
  return _socket.is_open();
}


std::string Socket::statusMessage() const
{
  return _socket.is_open()? "connection is open" : "warning: connection is closed";
}


bool Socket::open()
{
  auto endpoints = resolve(_host, _port, _io_context);
  boost::asio::connect(_socket, endpoints);
  return _socket.is_open();
}


void Socket::close()
{
  _socket.shutdown(shutdown_both);
  _socket.close();
}
