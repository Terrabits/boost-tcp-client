/**
 * \file block_data.cpp
 * \brief `rohdeschwarz::scpi::BlockData` implementation
 */


#include "rohdeschwarz/scpi/block_data.hpp"
using namespace rohdeschwarz::scpi;


// std lib
#include <algorithm>
#include <cctype>
#include <string>


BlockData::BlockData() :
  _isHeader(false),
  _headerSize_B (0),
  _payloadSize_B(0),
  _blockSize_B  (0)
{
  // no operations
}


BlockData::BlockData(std::vector<unsigned char> data) :
  _isHeader(false),
  _headerSize_B (0),
  _payloadSize_B(0),
  _blockSize_B  (0),
  _data(data)
{
  processHeader();
}


bool BlockData::isHeaderError() const
{
  if (isHeader())
  {
    // full, valid header
    return false;
  }

  if (_data.empty())
  {
    // no data to validate; no error yet...
    return false;
  }

  if (char(_data[0]) != '#')
  {
    // missing magic character
    return true;
  }

  if (_data.size() == 1)
  {
    // nothing else to check
    return false;
  }

  // check number of size digits
  if (!std::isdigit(char(_data[1])))
  {
    // error: not a number
    return true;
  }

  if (_data.size() == 2)
  {
    // nothing else to check
    return false;
  }

  // check available size digits
  const auto digits = std::min(parseNumberOfSizeDigits(), _data.size() - 2);
  for (std::size_t digit = 0; digit < digits; digit++)
  {
    if (!std::isdigit(_data[2 + digit]))
    {
      // error: not a number
      return true;
    }
  }

  // no errors found
  return false;
}


bool BlockData::isHeader() const
{
  return _isHeader;
}


bool BlockData::isComplete() const
{
  if (!isHeader())
  {
    return false;
  }
  return _data.size() >= _blockSize_B;
}


void BlockData::push_back(std::vector<unsigned char>::const_iterator begin, std::size_t size)
{
  if (isComplete())
  {
    // block needs no more data
    return;
  }

  if (!isHeader())
  {
    // copy all
    auto end = begin + size;
    _data.insert(_data.end(), begin, end);
    processHeader();
    return;
  }

  // get number of bytes to read from data
  const auto read_bytes = std::min(bytesRemaining(), size);

  // insert data and process
  auto end = begin + read_bytes;
  _data.insert(_data.end(), begin, end);
  processHeader();
}


std::size_t BlockData::size() const
{
  return _payloadSize_B;
}


unsigned char* BlockData::data()
{
  if (!isHeader())
  {
    // no payload
    return nullptr;
  }
  return _data.data() + _headerSize_B;
}


std::size_t BlockData::parseNumberOfSizeDigits() const
{
  if (_data.size() < 2)
  {
    // not enough data
    return 0;
  }

  // parse
  using char_p = char*;
  const char_p begin = char_p(_data.data() + 1);
  const std::string digit_str(begin, 1);
  return std::stoul(digit_str);
}


std::size_t BlockData::parsePayloadSize_B() const
{
  const std::size_t digits = parseNumberOfSizeDigits();
  if (!digits)
  {
    // cannot proceed
    return 0;
  }
  if (_data.size() < 2 + digits)
  {
    // not enough data
    return 0;
  }

  // parse
  using char_p = char*;
  const char_p begin = char_p(_data.data() + 2);
  std::string size_str(begin, digits);
  return std::stoul(size_str);
}


void BlockData::processHeader()
{
  if (isHeader())
  {
    // header already processed
    return;
  }

  if (isHeaderError())
  {
    // header is invalid; cannot process
    return;
  }

  // get number of header size digits
  const auto numberOfSizeDigits = parseNumberOfSizeDigits();
  if (!numberOfSizeDigits)
  {
    // cannot process (yet)
    return;
  }

  // payload size
  const std::size_t payloadSize_B = parsePayloadSize_B();
  if (!payloadSize_B)
  {
    // cannot process (yet)
    return;
  }

  // success
  _isHeader      = true;
  _headerSize_B  = 2 + numberOfSizeDigits;
  _payloadSize_B = payloadSize_B;
  _blockSize_B   = _headerSize_B + _payloadSize_B;
  _data.reserve(_blockSize_B);
}


std::size_t BlockData::bytesRemaining() const
{
  if (isComplete())
  {
    return 0;
  }

  return _blockSize_B - _data.size();
}
