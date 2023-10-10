/**
 * \file data_format.cpp
 * \brief RsVisa::DataFormat implementation
 */


#include "data_format.hpp"
#include "helpers.hpp"
#include "znx.hpp"
using namespace RsVisa;


DataFormat::DataFormat(Znx* znx) :
  _znx(znx)
{
  // no operations
}


bool DataFormat::isAscii()
{
  return dataFormat() == "ASC";
}


void DataFormat::setAscii()
{
  _znx->write(":FORM ASC");
}


bool DataFormat::isBinary32Bit()
{
  return dataFormat() == "REAL,32";
}


void DataFormat::setBinary32Bit()
{
  _znx->write(":FORM REAL,32");
}


bool DataFormat::isBinary64Bit()
{
  return dataFormat() == "REAL,64";
}


void DataFormat::setBinary64Bit()
{
  _znx->write(":FORM REAL,64");
}


bool DataFormat::isBigEndian()
{
  return byteOrder() == "NORM";
}


void DataFormat::setBigEndian()
{
  _znx->write(":FORM:BORD NORM");
}


bool DataFormat::isLittleEndian()
{
  return byteOrder() == "SWAP";
}


void DataFormat::setLittleEndian()
{
  _znx->write(":FORM:BORD SWAP");
}


// helpers

std::string DataFormat::dataFormat()
{
  return rightTrim(_znx->query(":FORM?"));
}


std::string DataFormat::byteOrder()
{
  return rightTrim(_znx->query(":FORM:BORD?"));
}
