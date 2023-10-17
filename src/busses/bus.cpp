/**
 * \file  bus.hpp
 * \brief rohdeschwarz::busses::Bus class definition
 */


// rohdeschwarz
#include "rohdeschwarz/busses/bus.hpp"
using namespace rohdeschwarz::busses;


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


unsigned char* Bus::data()
{
  return _buffer.data();
}


const unsigned char* Bus::data() const
{
  return _buffer.data();
}


std::size_t Bus::bufferSize_B() const
{
  return _buffer.size();
}


void Bus::setBufferSize(std::size_t bytes)
{
  _buffer.resize(bytes);
}


bool Bus::readData(std::size_t* readSize)
{
  return readData(_buffer.data(), _buffer.size(), readSize);
}


std::string Bus::read()
{
  // read data
  std::size_t readSize;
  if (!readData(&readSize))
  {
    // read failed
    return std::string();
  }

  // copy data to string
  char_p data_ptr = char_p(data());
  return std::string(data_ptr, readSize);
}


bool Bus::write(const std::string& scpi)
{
  uchar_p data_ptr = uchar_p(scpi.c_str());
  return writeData(data_ptr, scpi.size());
}


std::string Bus::query(const std::string& scpi)
{
  if (!write(scpi))
  {
    // write failed
    return std::string();
  }
  return read();
}


bool Bus::write(const char* scpi)
{
  // TODO
  return false;
}


bool Bus::write(const char* scpi, std::size_t size)
{
  // TODO
  return false;
}


std::string Bus::query(const char* scpi)
{
  // TODO
  return std::string();
}


std::string Bus::query(const char* scpi, std::size_t size)
{
  // TODO
  return std::string();
}
