/**
 * \file  buffer.cpp
 * \brief rohdeschwarz::Buffer class implementation
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/buffer.hpp"
using namespace rohdeschwarz::busses::socket;


Buffer::Buffer(std::size_t size) :
  _buffer(size)
{
  // pass
}


std::size_t Buffer::size() const
{
  return _buffer.size();
}


void Buffer::resize(std::size_t size)
{
  _buffer.resize(size);
}


char* Buffer::data()
{
  return _buffer.data();
}


const char* Buffer::data() const
{
  return _buffer.data();
}


std::string Buffer::toString() const
{
  return std::string(data());
}


std::string Buffer::toString(std::size_t size) const
{
  return std::string(data(), size);
}


boost::asio::mutable_buffer Buffer::toMutableBuffer()
{
  return boost::asio::buffer(data(), size());
}


boost::asio::const_buffer Buffer::toConstBuffer() const
{
  return boost::asio::buffer(data(), size());
}
