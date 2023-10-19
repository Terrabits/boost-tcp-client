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
  return std::stoi(_vna->query(":SENS%1%:SWE:POIN?", index()));
}


void Channel::setPoints(unsigned int points)
{
  _vna->write(":SENS%1%:SWE:POIN %2%", index(), points);
}


double Channel::startFrequency_Hz()
{
  return std::stod(_vna->query(":SENS%1%:FREQ:STAR?", _index));
}


void Channel::setStartFrequency(double frequency_Hz)
{
  _vna->write(":SENS%1%:FREQ:STAR %2%", _index, frequency_Hz);
}


double Channel::stopFrequency_Hz()
{
  return std::stod(_vna->query(":SENS%1%:FREQ:STOP?", _index));
}


void Channel::setStopFrequency(double frequency_Hz)
{
  _vna->write(":SENS%1%:FREQ:STOP %2%", _index, frequency_Hz);
}


std::vector<double> Channel::frequencies_Hz()
{
  // set data format to binary 64-bit, little-endian
  PreserveDataFormat preserve_data_format(_vna);
  DataFormat format = _vna->dataFormat();
  format.setBinary64Bit();
  format.setLittleEndian();

  // write
  if (!_vna->write(":CALC%1%:DATA:STIM?", _index))
  {
    // error
    return std::vector<double>();
  }

  // read
  return _vna->read64BitVector();
}
