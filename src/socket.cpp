// socket
#include "rohdeschwarz/socket.hpp"
using namespace RohdeSchwarz;


// boost
using boost::asio::ip::tcp;


// std lib
#include <cstring>


// constants
const std::size_t DEFAULT_BUFFER_SIZE_B = 5 * 1024;  // 5 kB


Socket::Socket(const char* address, int port) :
  _address(address),
  _port(port),
  _io_context(),
  _socket(_io_context),
  _buffer(DEFAULT_BUFFER_SIZE_B)
{
  open();
}


Socket::Socket(const std::string& address, int port) :
  _address(address),
  _port(port),
  _io_context(),
  _socket(_io_context),
  _buffer(DEFAULT_BUFFER_SIZE_B)
{
  open();
}


Socket::~Socket()
{
  close();
}


std::string Socket::address() const
{
  return _address;
}


int Socket::port() const
{
  return _port;
}


std::size_t Socket::bufferSize_B() const
{
  return _buffer.size();
}


void Socket::setBufferSize(std::size_t bufferSize_B)
{
  _buffer.setSize(bufferSize_B);
}


std::string Socket::read()
{
  std::size_t size = boost::asio::read(_socket, getBuffer());
  return std::string(_buffer.data(), size);
}


std::string Socket::read(std::size_t bufferSize_B)
{
  // create buffer
  Buffer buffer(bufferSize_B);

  // read
  std::size_t size = boost::asio::read(_socket, getBuffer(_buffer));
  return std::string(buffer.data(), size);
}


std::size_t Socket::write(const char* data)
{
  const std::size_t size = std::strlen(data);
  return write(data, size);
}


std::size_t Socket::write(const char* data, std::size_t size)
{
  auto buffer = getBuffer(data, size);
  return boost::asio::write(_socket, buffer);
}


std::size_t Socket::write(const std::string& data)
{
  auto buffer = getBuffer(data.c_str(), data.size());
  return boost::asio::write(_socket, buffer);
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


boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type Socket::resolve_endpoints()
{
  std::string port = std::to_string(_port);
  boost::asio::ip::tcp::resolver resolver(_io_context);
  return resolver.resolve(_address.c_str(), port.c_str());
}


boost::asio::mutable_buffer Socket::getBuffer()
{
  return getBuffer(_buffer.data(), _buffer.size());
}


boost::asio::mutable_buffer Socket::getBuffer(Buffer& buffer)
{
  return boost::asio::buffer(buffer.data(), buffer.size());
}


boost::asio::mutable_buffer Socket::getBuffer(char* buffer, std::size_t size)
{
  return boost::asio::buffer(buffer, size);
}


boost::asio::const_buffer Socket::getBuffer(const char* buffer, std::size_t size)
{
  return boost::asio::buffer(buffer, size);
}


bool Socket::open()
{
  // resolve ip address, port
  auto endpoints = resolve_endpoints();

  // connect
  boost::asio::connect(_socket, endpoints);
  return _socket.is_open();
}


void Socket::close()
{
  _socket.shutdown(tcp::socket::shutdown_both);
  _socket.close();
}
