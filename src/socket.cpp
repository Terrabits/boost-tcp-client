/**
 * \file  socket.cpp
 * \brief RohdeSchwarz::Socket class implementation
 */


// rohdeschwarz
#include "rohdeschwarz/socket.hpp"
using namespace RohdeSchwarz;


// boost
using boost::asio::ip::tcp;


// std lib
#include <cstring>


// constants
const std::size_t DEFAULT_BUFFER_SIZE_B = 5 * 1024;  // 5 kB


Socket::Socket(const char* host, int port) :
  _address(host, port),
  _buffer(DEFAULT_BUFFER_SIZE_B),
  _socket(_io_context)
{
  open();
}


Socket::Socket(const std::string& host, int port) :
  _address(host, port),
  _buffer(DEFAULT_BUFFER_SIZE_B),
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
  return _address.host();
}


int Socket::port() const
{
  return _address.port();
}


std::size_t Socket::bufferSize_B() const
{
  return _buffer.size();
}


void Socket::setBufferSize(std::size_t size_B)
{
  _buffer.resize(size_B);
}


std::string Socket::read()
{
  auto mutable_buffer = _buffer.toMutableBuffer();
  auto size           = boost::asio::read(_socket, mutable_buffer);
  return _buffer.toString(size);
}


std::string Socket::read(std::size_t bufferSize_B)
{
  // create mutable buffer
  Buffer buffer(bufferSize_B);
  auto mutable_buffer = buffer.toMutableBuffer();

  // read
  auto size = boost::asio::read(_socket, mutable_buffer);
  return buffer.toString(size);
}


std::size_t Socket::write(const char* data)
{
  auto size = std::strlen(data);
  return write(data, size);
}


std::size_t Socket::write(const char* data, std::size_t size)
{
  auto const_buffer = boost::asio::buffer(data, size);
  return boost::asio::write(_socket, const_buffer);
}


std::size_t Socket::write(const std::string& data)
{
  auto const_buffer = boost::asio::buffer(data.c_str(), data.size());
  return boost::asio::write(_socket, const_buffer);
}


std::string Socket::query(const char* scpi)
{
  // write
  if (write(scpi) == 0)
  {
    // write failed
    return std::string();
  }

  // read
  return read();
}


std::string Socket::query(const char* scpi, std::size_t bufferSize_B)
{
  // write
  if (write(scpi) == 0)
  {
    // write failed
    return std::string();
  }

  // read
  return read(bufferSize_B);
}


std::string Socket::query(const std::string& scpi)
{
  // write
  if (write(scpi) == 0)
  {
    // write failed
    return std::string();
  }

  // read
  return read();
}


std::string Socket::query(const std::string& scpi, std::size_t bufferSize_B)
{
  // write
  if (write(scpi) == 0)
  {
    // write failed
    return std::string();
  }

  // read
  return read(bufferSize_B);
}


bool Socket::open()
{
  // resolve host, port
  auto endpoints = _address.resolve(_io_context);

  // connect
  boost::asio::connect(_socket, endpoints);
  return _socket.is_open();
}


void Socket::close()
{
  _socket.shutdown(tcp::socket::shutdown_both);
  _socket.close();
}
