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
using char_p       = char*;
using const_char_p = const char*;


Socket::Socket(const char* host, int port) :
  _host(host),
  _port(port),
  _socket(_io_context)
{
  open();
}


Socket::Socket(const std::string& host, int port) :
  _host(host),
  _port(port),
  _socket(_io_context)

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

  // read error?
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

  // write error?
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
