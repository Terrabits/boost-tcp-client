// rohdeschwarz
#include "rohdeschwarz/buffer.hpp"
using namespace RohdeSchwarz;


Buffer::Buffer(std::size_t size) :
  _size(size),
  _buffer(new char[size])
{
  // pass
}


Buffer::~Buffer()
{
  _buffer.reset();
}


std::size_t Buffer::size() const
{
  return _size;
}


void Buffer::setSize(std::size_t size)
{
  // TODO: thread safety?
  _size = size;
  _buffer.reset(new char[size]);
}


char* Buffer::data()
{
  return _buffer.get();
}


const char* Buffer::data() const
{
  return _buffer.get();
}
