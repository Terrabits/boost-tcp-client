/**
 * \file instrument.cpp
 * \brief rohdeschwarz::instruments::Instrument implementation
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/socket.hpp"
#include "rohdeschwarz/busses/visa/visa.hpp"
#include "rohdeschwarz/instruments/instrument.hpp"
#include "rohdeschwarz/instruments/preserve_timeout.hpp"
#include "rohdeschwarz/scpi/bool.hpp"
#include "rohdeschwarz/helpers.hpp"
#include "rohdeschwarz/to_vector.hpp"
using namespace rohdeschwarz::busses::socket;
using namespace rohdeschwarz::busses::visa;
using namespace rohdeschwarz::instruments;
using namespace rohdeschwarz::scpi;
using namespace rohdeschwarz;


// std lib
#include <cstring>
#include <sstream>


// types
using const_char_p = const char*;


bool Instrument::isOpen() const
{
  return _bus != nullptr;
}


bool Instrument::openVisa(std::string resource, unsigned int timeout_ms)
{
  // connect to resource
  using rohdeschwarz::busses::visa::system_error;
  try
  {
    _bus.reset(new Visa(resource, timeout_ms));
  }

  // error
  catch (const system_error& error)
  {
    return false;
  }

  // success
  return true;
}


bool Instrument::openTcp(std::string host, unsigned int timeout_ms)
{
  // connect to host
  using rohdeschwarz::busses::socket::system_error;
  try
  {
    _bus.reset(new Socket(host, timeout_ms));
  }

  // error
  catch (const system_error& error)
  {
    return false;
  }

  // success
  return true;
}


void Instrument::close()
{
  _bus.reset();
}


std::size_t Instrument::bufferSize_B() const
{
  return _bus->bufferSize_B();
}


void Instrument::setBufferSize(std::size_t size_bytes)
{
  _bus->setBufferSize(size_bytes);
}


std::vector<unsigned char>* Instrument::buffer()
{
  return _bus->buffer();
}

const std::vector<unsigned char>* Instrument::buffer() const
{
  return _bus->buffer();
}

std::vector<unsigned char> Instrument::takeData()
{
  return _bus->takeData();
}


int Instrument::timeout_ms()
{
  return _bus->timeout_ms();
}


bool Instrument::setTimeout(int timeout_ms)
{
  return _bus->setTimeout(timeout_ms);
}


bool Instrument::readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize)
{
  return _bus->readData(buffer, bufferSize, readSize);
}


bool Instrument::writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize)
{
  return _bus->writeData(data, dataSize, writeSize);
}


bool Instrument::readData(std::size_t* readSize)
{
  return _bus->readData(readSize);
}


std::string Instrument::read()
{
  // read data
  std::size_t size;
  if (!readData(&size))
  {
    // error
    return std::string();
  }

  // convert to string
  auto data = const_char_p(buffer()->data());
  return std::string(data, size);
}


std::vector<double> Instrument::readAsciiVector()
{
  // TODO
  return std::vector<double>();
}


std::vector<std::complex<double>> Instrument::readAsciiComplexVector()
{
  // TODO
  return std::vector<std::complex<double>>();
}


scpi::BlockData Instrument::readBlockData()
{
  // read initial data
  std::size_t read_size;
  if (!readData(&read_size))
  {
    // error
    return scpi::BlockData();
  }

  // take initial data from buffer
  auto data = takeData();
  data.resize(read_size);

  // create block
  scpi::BlockData block_data(std::move(data));

  // read until block data is complete
  while (!block_data.isComplete())
  {
    if (block_data.isHeaderError())
    {
      // cannot complete block without header
      return scpi::BlockData();
    }

    // read more data
    if (!readData(&read_size))
    {
      // error
      return BlockData();
    }

    // push data to block
    const auto begin = buffer()->begin();
    block_data.push_back(begin, read_size);
  }

  // block data is complete
  return block_data;
}


std::vector<double> Instrument::read64BitVector()
{
  // read block data
  BlockData data = readBlockData();
  if (!data.isComplete())
  {
    // error
    return std::vector<double>();
  }

  // parse block data
  return to_vector<double>(data.data(), data.size());
}


std::vector<std::complex<double>> Instrument::read64BitComplexVector()
{
  // read block data
  BlockData data = readBlockData();
  if (!data.isComplete())
  {
    // error
    return std::vector<std::complex<double>>();
  }

  // parse block data
  return to_vector_complex_double(data.data(), data.size());
}


bool Instrument::isBusError() const
{
  return _bus->isError();
}


std::string Instrument::busStatus() const
{
  return _bus->statusMessage();
}


std::string Instrument::id()
{
  return trim(query("*IDN?"));
}


std::string Instrument::options()
{
  return trim(query("*OPT?"));
}


void Instrument::clearErrors()
{
  write("*CLS");
}


void Instrument::preset()
{
  write("*RST");
}


void Instrument::wait()
{
  write("*WAI");
}


bool Instrument::blockUntilOperationComplete(unsigned int timeout_ms)
{
  PreserveTimeout preserve_timeout(this);
  setTimeout(timeout_ms);
  return queryScpiBool("*OPC?");
}
