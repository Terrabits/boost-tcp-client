/**
 * \file data_format.cpp
 * \brief rohdeschwarz::instruments::vna::DataFormat implementation
 */


// rohdeschwarz
#include "rohdeschwarz/instruments/vna/data_format.hpp"
#include "rohdeschwarz/instruments/vna/vna.hpp"
#include "rohdeschwarz/helpers.hpp"
using namespace rohdeschwarz;
using namespace rohdeschwarz::instruments::vna;


DataFormat::DataFormat(Vna* znx) :
  _vna(znx)
{
  // no operations
}


bool DataFormat::isAscii()
{
  return dataFormat() == "ASC";
}


void DataFormat::setAscii()
{
  _vna->write(":FORM ASC");
}


bool DataFormat::isBinary32Bit()
{
  return dataFormat() == "REAL,32";
}


void DataFormat::setBinary32Bit()
{
  _vna->write(":FORM REAL,32");
}


bool DataFormat::isBinary64Bit()
{
  return dataFormat() == "REAL,64";
}


void DataFormat::setBinary64Bit()
{
  _vna->write(":FORM REAL,64");
}


bool DataFormat::isBigEndian()
{
  return byteOrder() == "NORM";
}


void DataFormat::setBigEndian()
{
  _vna->write(":FORM:BORD NORM");
}


bool DataFormat::isLittleEndian()
{
  return byteOrder() == "SWAP";
}


void DataFormat::setLittleEndian()
{
  _vna->write(":FORM:BORD SWAP");
}


// helpers

std::string DataFormat::dataFormat()
{
  return rightTrim(_vna->query(":FORM?"));
}


std::string DataFormat::byteOrder()
{
  return rightTrim(_vna->query(":FORM:BORD?"));
}
