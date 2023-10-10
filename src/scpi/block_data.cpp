/**
 * \file block_data.cpp
 * \brief `RsVisa::BlockData` implementation
 */


#include "block_data.hpp"
using namespace RsVisa;


// std lib
#include <algorithm>
#include <cctype>
#include <string>


// types
using uint = unsigned int;

BlockData::BlockData() :
  _isHeader(false),
  _headerSize_B (0),
  _payloadSize_B(0),
  _blockSize_B  (0)
{
  // no operations
}


BlockData::BlockData(const std::vector<unsigned char> &data) :
  _isHeader(false),
  _headerSize_B (0),
  _payloadSize_B(0),
  _blockSize_B  (0),
  _data(data)
{
  processHeader();
}


BlockData::BlockData(std::vector<unsigned char>&& data) :
  _isHeader(false),
  _headerSize_B (0),
  _payloadSize_B(0),
  _blockSize_B  (0),
  _data(data)
{
  processHeader();
}


bool BlockData::isPartialHeader() const
{
  if (isHeader())
  {
    // full header
    return true;
  }

  if (_data.empty())
  {
    // no data;
    // default to true
    return true;
  }

  if (char(_data[0]) != '#')
  {
    // missing magic character
    return false;
  }

  if (_data.size() == 1)
  {
    // nothing else to check
    return true;
  }

  // check number of size digits
  if (!std::isdigit(char(_data[1])))
  {
    // invalid
    return false;
  }

  if (_data.size() == 2)
  {
    // nothing else to check
    return true;
  }

  // check available size digits
  const uint digits = std::min(parseNumberOfSizeDigits(), uint(_data.size() - 2));
  for (uint digit = 0; digit < digits; digit++)
  {
    if (!std::isdigit(_data[2 + digit]))
    {
      // invalid
      return false;
    }
  }

  // no errors found
  return true;
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


void BlockData::push_back(const std::vector<unsigned char>& data)
{
  if (isComplete())
  {
    // payload already complete
    return;
  }

  if (data.empty())
  {
    // nothing to push back
    return;
  }

  // find last byte to insert
  auto data_end = data.end();
  if (isHeader())
  {
    // only insert necessary, valid data
    const uint bytesToRead = std::min(bytesRemaining(), uint(data.size()));
    data_end = data.begin() + bytesToRead;
  }

  // insert and process
  _data.insert(_data.end(), data.begin(), data_end);
  processHeader();
}


void BlockData::push_back(std::vector<unsigned char>&& data)
{
  push_back(data);
}


unsigned int BlockData::payloadSize_B() const
{
  return _payloadSize_B;
}


unsigned char* BlockData::payload()
{
  if (!isHeader())
  {
    // no payload
    return nullptr;
  }
  return _data.data() + _headerSize_B;
}


unsigned int BlockData::parseNumberOfSizeDigits() const
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


unsigned int BlockData::parsePayloadSize_B() const
{
  const uint digits = parseNumberOfSizeDigits();
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
    // already processed
    return;
  }

  if (!isPartialHeader())
  {
    // header is invalid
    return;
  }

  // header size digits
  const uint numberOfSizeDigits = parseNumberOfSizeDigits();
  if (!numberOfSizeDigits)
  {
    // cannot process
    return;
  }

  // payload size
  const uint payloadSize_B = parsePayloadSize_B();
  if (!payloadSize_B)
  {
    // cannot process
    return;
  }

  // success
  _isHeader      = true;
  _headerSize_B  = 2 + numberOfSizeDigits;
  _payloadSize_B = payloadSize_B;
  _blockSize_B   = _headerSize_B + _payloadSize_B;
  _data.reserve(_blockSize_B);
}


unsigned int BlockData::bytesRemaining() const
{
  if (isComplete())
  {
    return 0;
  }

  return uint(_blockSize_B - _data.size());
}
