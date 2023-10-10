/**
 * \file preserve_data_format.cpp
 * \brief RsVisa::PreserveDataFormat implementation
 */


#include "preserve_data_format.hpp"
using namespace RsVisa;


PreserveDataFormat::PreserveDataFormat(Znx *znx) :
  _dataFormat(znx->dataFormat())
{
  _isBinary    = !_dataFormat.isAscii();
  _is64Bit     = _dataFormat.isBinary64Bit();
  _isBigEndian = _dataFormat.isBigEndian();
}


PreserveDataFormat::~PreserveDataFormat()
{
  if (!_isBinary)
  {
    // ascii
    _dataFormat.setAscii();
    return;
  }

  // binary
  restoreBinaryBits();
  restoreByteOrder();
}


void PreserveDataFormat::restoreBinaryBits()
{
  if (_is64Bit)
  {
    // 64 bit
    _dataFormat.setBinary64Bit();
    return;
  }

  // 32 bit
  _dataFormat.setBinary32Bit();
}


void PreserveDataFormat::restoreByteOrder()
{
  if (_isBigEndian)
  {
    // big endian
    _dataFormat.setBigEndian();
    return;
  }

  // little endian
  _dataFormat.setLittleEndian();
}
