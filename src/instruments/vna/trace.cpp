/**
 * \file trace.cpp
 * \brief rohdeschwarz::instruments::vna::Trace implementation
 */


// rohdeschwarz
#include "rohdeschwarz/instruments/vna/preserve_data_format.hpp"
#include "rohdeschwarz/instruments/vna/trace.hpp"
#include "rohdeschwarz/instruments/vna/vna.hpp"
#include "rohdeschwarz/helpers.hpp"
#include "rohdeschwarz/to_vector.hpp"
using namespace rohdeschwarz;
using namespace rohdeschwarz::instruments::vna;


Trace::Trace(Vna* znx, const char* name) :
  _vna(znx),
  _name(name)
{
  // no operations
}


Trace::Trace(Vna* znx, const std::string& name) :
  _vna(znx),
  _name(name)
{
  // no operations
}


std::string Trace::name() const
{
  return _name;
}


void Trace::select()
{
  _vna->write(":CALC%1%:PAR:SEL \'%2%\'", channel(), _name);
}


std::string Trace::parameter()
{
  const auto response = _vna->query(":CALC%1%:PAR:MEAS? \'%2%\'", channel(), _name);
  return unquote(rightTrim(response));
}


void Trace::setParameter(const char* parameter)
{
  const std::string parameter_str(parameter);
  setParameter(parameter_str);
}


void Trace::setParameter(const std::string& parameter)
{
  _vna->write(":CALC%1%:PAR:MEAS \'%2%\',\'%3%\'", channel(), _name, parameter);
}


std::string Trace::format()
{
  select();
  const auto response = _vna->query(":CALC%1%:FORM?", channel());
  return rightTrim(response);
}


void Trace::setFormat(const char* format)
{
  const std::string format_str(format);
  setFormat(format_str);
}


void Trace::setFormat(const std::string& format)
{
  select();
  _vna->write(":CALC%1%:FORM %2%", channel(), format);
}


unsigned int Trace::channel()
{
  return std::stoi(_vna->query(":CONF:TRAC:CHAN:NAME:ID? \'%1%\'", _name));
}

unsigned int Trace::diagram()
{
  auto response = _vna->query(":CONF:TRAC:WIND? \'%1%\'", _name);
  return std::stoi(rightTrim(response));
}


void Trace::setDiagram(unsigned int diagram)
{
  _vna->write(":DISP:WIND%1%:TRAC:EFE \'%2%\'", diagram, _name);
}


std::vector<double> Trace::y()
{
  // set data format to binary 64-bit, little-endian
  PreserveDataFormat preserve_data_format(_vna);
  DataFormat format = _vna->dataFormat();
  format.setBinary64Bit();
  format.setLittleEndian();

  // write
  if (!_vna->write("CALC:DATA:TRAC? \'%1%\',FDAT", name()))
  {
    // error
    return std::vector<double>();
  }

  // read
  return _vna->read64BitVector();
}


std::vector<std::complex<double>> Trace::y_complex()
{
  // set data format to binary 64-bit, little-endian
  PreserveDataFormat preserve_data_format(_vna);
  DataFormat format = _vna->dataFormat();
  format.setBinary64Bit();
  format.setLittleEndian();

  // write
  if (!_vna->write(":CALC:DATA:TRAC? \'%1%\',SDAT", name()))
  {
    // error
    return std::vector<std::complex<double>>();
  }

  // read
  return _vna->read64BitComplexVector();
}
