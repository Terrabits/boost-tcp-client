/**
 * \file channel.cpp
 * \brief rohdeschwarz::instruments::vna::Channel implementation
 */


// rohdeschwarz
#include "rohdeschwarz/instruments/vna/channel.hpp"
#include "rohdeschwarz/instruments/vna/preserve_data_format.hpp"
#include "rohdeschwarz/instruments/vna/vna.hpp"
#include "rohdeschwarz/to_vector.hpp"
using namespace rohdeschwarz;
using namespace rohdeschwarz::instruments::vna;


// std lib
#include <sstream>


Channel::Channel(Vna *znx, unsigned int index) :
  _vna(znx),
  _index(index)
{
  // no operations
}


unsigned int Channel::index() const
{
  return _index;
}


unsigned int Channel::points()
{
  // :SENS<ch>:SWE:POIN?
  std::stringstream scpi;
  scpi << ":SENS" << index();
  scpi << ":SWE:POIN?";
  return std::stoi(_vna->query(scpi.str()));
}


void Channel::setPoints(unsigned int points)
{
  // :SENS<ch>:SWE:POIN <points>
  std::stringstream scpi;
  scpi << ":SENS"      << index();
  scpi << ":SWE:POIN " << points;
  _vna->write(scpi.str());
}


double Channel::startFrequency_Hz()
{
  // :SENS<ch>:FREQ:STAR?
  std::stringstream scpi;
  scpi << ":SENS" << _index;
  scpi << ":FREQ:STAR?";
  return std::stod(_vna->query(scpi.str()));
}


void Channel::setStartFrequency(double frequency_Hz)
{
  // :SENS<ch>:FREQ:STAR <frequency_Hz>
  std::stringstream scpi;
  scpi << ":SENS"       << _index;
  scpi << ":FREQ:STAR " << frequency_Hz;
  _vna->write(scpi.str());
}


double Channel::stopFrequency_Hz()
{
  // :SENS<ch>:FREQ:STOP?
  std::stringstream scpi;
  scpi << ":SENS" << _index;
  scpi << ":FREQ:STOP?";
  return std::stod(_vna->query(scpi.str()));
}


void Channel::setStopFrequency(double frequency_Hz)
{
  // :SENS<ch>:FREQ:STOP <frequency_Hz>
  std::stringstream scpi;
  scpi << ":SENS"       << _index;
  scpi << ":FREQ:STOP " << frequency_Hz;
  _vna->write(scpi.str());
}


std::vector<double> Channel::frequencies_Hz()
{
  // calculate buffer size (Bytes)
  // note: requires points() scpi query
  using uint = unsigned int;
  const uint points      = this->points();
  const uint bytes_per_point = 8;
  const uint payload     = points * bytes_per_point;
  const uint header      = 2 + uint(std::to_string(payload).size());
  const uint buffer_size = header + payload;

  // construct scpi command
  std::stringstream stream;
  stream << ":CALC" << _index;
  stream << ":DATA:STIM?";
  const std::string scpi = stream.str();

  // set data format to
  // binary 64-bit, little endian
  PreserveDataFormat preserve_data_format(_vna);
  DataFormat format = _vna->dataFormat();
  format.setBinary64Bit();
  format.setLittleEndian();

  // query frequencies block data
  scpi::BlockData block_data = _vna->queryBlockData(scpi, buffer_size + 1);
  if (!block_data.isComplete())
  {
    // query failed
    return std::vector<double>();
  }

  // return frequencies vector
  return toVector<double>(block_data.payload(), block_data.payloadSize_B());
}
