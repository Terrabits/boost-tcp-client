/**
 * \file  bus.hpp
 * \brief rohdeschwarz::busses::Bus class definition
 */


// rohdeschwarz
#include "rohdeschwarz/busses/bus.hpp"
using namespace rohdeschwarz::busses;


// std lib
#include <utility>


// constants
const std::size_t _50_KB_ = 50 * 1024;


// types
using char_p  = char*;
using uchar_p = unsigned char*;


// implementation


Bus::Bus() :
  _buffer(_50_KB_)
{
  // pass
}


Bus::~Bus()
{
  // pass
}


std::size_t Bus::bufferSize_B() const
{
  return _buffer.size();
}


void Bus::setBufferSize(std::size_t bytes)
{
  _buffer.resize(bytes);
}


std::vector<unsigned char>* Bus::buffer()
{
  return &_buffer;
}


const std::vector<unsigned char>* Bus::buffer() const
{
  return &_buffer;
}


std::vector<unsigned char> Bus::takeData()
{
  auto buffer = std::move(_buffer);
  setBufferSize(buffer.size());
  return buffer;
}


bool Bus::readData(std::size_t* readSize)
{
  return readData(_buffer.data(), _buffer.size(), readSize);
}
