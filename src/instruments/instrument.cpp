/**
 * \file instrument.cpp
 * \brief RsVisa::Instrument implementation
 */


#include "instrument.hpp"


// RsVisa
#include "bool.hpp"
#include "helpers.hpp"
#include "preserve_timeout.hpp"
using namespace RsVisa;


// std lib
#include <cstring>
#include <sstream>


Instrument::Instrument()
  : _resource_manager(VI_NULL),
    _instrument(VI_NULL),
    _status(VI_SUCCESS)
{
  // TODO: throw exception on error?
  openDefaultRM();
}


Instrument::~Instrument()
{
  if (isOpen())
  {
    close();
  }
}


bool Instrument::isVisa() const
{
  return _visa.isVisa();
}


bool Instrument::isOpen() const
{
  return _instrument != VI_NULL;
}


bool Instrument::open(const char* resource, unsigned int timeout_ms)
{
  const std::string resource_str(resource);
  return open(resource_str, timeout_ms);
}


bool Instrument::open(const std::string& resource, unsigned int timeout_ms)
{
  // open
  _status = _visa.viOpen(
    _resource_manager,
    ViRsrc(resource.c_str()),
    ViUInt32(VI_NULL), // mode
    ViUInt32(timeout_ms),
    &_instrument
  );

  if (isError())
  {
    // connection failed
    close();
    return false;
  }

  // success
  return true;
}


bool Instrument::close()
{
  if (isOpen())
  {
    // close connection
    _status = _visa.viClose(ViObject(_instrument));
    if (_status < VI_SUCCESS)
    {
      // close failed
      return false;
    }
  }

  // clear instrument session
  _instrument = VI_NULL;
  return true;
}


int Instrument::timeout_ms()
{
  return int(attribute(VI_ATTR_TMO_VALUE));
}


bool Instrument::setTimeout(int timeout_ms)
{
  return setAttribute(VI_ATTR_TMO_VALUE, ViAttrState(timeout_ms));
}


void Instrument::binaryWrite(const std::vector<unsigned char> &data)
{
  ViUInt32 bytes_written;
  _status = _visa.viWrite(
    _instrument,
    ViBuf(data.data()),
    ViUInt32(data.size()),
    &bytes_written
  );
}


std::vector<unsigned char> Instrument::binaryRead(unsigned int bufferSize_B)
{
  std::vector<unsigned char> buffer(bufferSize_B);
  ViUInt32 bytes_read;
  _status = _visa.viRead(
    _instrument,
    buffer.data(),
    bufferSize_B,
    &bytes_read
  );
  return buffer;
}


std::vector<unsigned char> Instrument::binaryQuery(std::vector<unsigned char> scpi, unsigned int bufferSize_B)
{
  binaryWrite(scpi);
  if (isError())
  {
    // write failed
    return std::vector<unsigned char>();
  }
  return binaryRead(bufferSize_B);
}


void Instrument::write(const std::string &scpi)
{
  binaryWrite(binaryCopy(scpi));
}


BlockData Instrument::readBlockData(unsigned int bufferSize_B)
{
  BlockData data(binaryRead(bufferSize_B));
  if (isError())
  {
    return BlockData();
  }

  while (!data.isComplete())
  {
    if (!data.isPartialHeader())
    {
      // header error; return empty data
      return BlockData();
    }

    // read more data
    data.push_back(binaryRead());
    if (isError())
    {
      // visa error
      return BlockData();
    }
  }

  // block data is complete
  return data;
}


BlockData Instrument::queryBlockData(const std::string &scpi, unsigned int bufferSize_B)
{
  write(scpi);
  if (isError())
  {
    return BlockData();
  }

  return readBlockData(bufferSize_B);
}


std::string Instrument::read(unsigned int bufferSize_B)
{
  using char_p = char*;
  const std::vector<unsigned char> buffer = binaryRead(bufferSize_B);
  return std::string(char_p(buffer.data()));
}


std::string Instrument::query(const std::string &scpi, unsigned int bufferSize_B)
{
  write(scpi);
  if (isError())
  {
    // write failed
    return std::string();
  }
  return read(bufferSize_B);
}


bool Instrument::isError() const
{
  return _status < VI_SUCCESS;
}


ViStatus Instrument::status() const
{
  return _status;
}


std::string Instrument::statusMessage()
{
  ViChar description[1000];
  _status = _visa.viStatusDesc(
    _instrument,
    _status,
    description
  );
  return std::string(description);
}


std::string Instrument::id()
{
  return rightTrim(query("*IDN?"));
}


std::string Instrument::options()
{
  return rightTrim(query("*OPT?"));
}


void Instrument::clearErrors()
{
  write("*CLS");
}


void Instrument::reset()
{
  write("*RST");
}


void Instrument::wait()
{
  write("*WAI");
}


bool Instrument::isOperationComplete()
{
  return toBool(query("*OPC"));
}


bool Instrument::blockUntilOperationComplete(unsigned int timeout_ms)
{
  PreserveTimeout preserve_timeout(this);
  setTimeout(timeout_ms);
  return toBool(query("*OPC?"));
}


bool Instrument::openDefaultRM()
{
  _status = _visa.viOpenDefaultRM(&_resource_manager);
  return !isError();
}


ViAttrState Instrument::attribute(ViAttr attribute)
{
  // value pointer type
  using void_p = void _VI_PTR;

  // get attribute
  ViAttrState value = 0;
  _status = _visa.viGetAttribute(_instrument, attribute, void_p(&value));
  return value;
}


bool Instrument::setAttribute(ViAttr attribute, ViAttrState value)
{
  _status = _visa.viSetAttribute(_instrument, attribute, value);
  return isError();
}


std::vector<unsigned char> Instrument::binaryCopy(const std::string &input)
{
  // prepare binary buffer
  std::vector<unsigned char> output;
  output.resize(input.size() + 5);

  // copy to buffer
  using char_p = char*;
  strncpy_s(char_p(output.data()), output.size(), input.c_str(), _TRUNCATE);
  return output;
}
