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


// std lib
#include <sstream>


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
  // CALC<Ch>:PAR:SEL '<name>'
  std::stringstream scpi;
  scpi << ":CALC" << channel();
  scpi << ":PAR:SEL ";
  scpi << quote(_name);
  _vna->write(scpi.str());
}


std::string Trace::parameter()
{
  // CALC<Ch>:PAR:MEAS? '<name>'
  std::stringstream scpi;
  scpi << ":CALC" << channel();
  scpi << ":PAR:MEAS? ";
  scpi << quote(_name);
  const std::string response = _vna->query(scpi.str());
  return unquote(rightTrim(response));
}


void Trace::setParameter(const char* parameter)
{
  const std::string parameter_str(parameter);
  setParameter(parameter_str);
}


void Trace::setParameter(const std::string& parameter)
{
  // CALC<Ch>:PAR:MEAS '<name>','<parameter>'
  std::stringstream scpi;
  scpi << ":CALC" << channel();
  scpi << ":PAR:MEAS ";
  scpi << quote(_name) << ",";
  scpi << quote(parameter);
  _vna->write(scpi.str());
}


std::string Trace::format()
{
  // CALC<Ch>:FORM?
  select();

  std::stringstream scpi;
  scpi << ":CALC" << channel();
  scpi << ":FORM?";
  return rightTrim(_vna->query(scpi.str()));
}


void Trace::setFormat(const char* format)
{
  const std::string format_str(format);
  setFormat(format_str);
}


void Trace::setFormat(const std::string& format)
{
  select();

  // CALC<Ch>:FORM <format>
  std::stringstream scpi;
  scpi << ":CALC" << channel();
  scpi << ":FORM " << format;
  _vna->write(scpi.str());
}


unsigned int Trace::channel()
{
  // CONF:TRAC:CHAN:NAME:ID? '<name>'
  std::stringstream scpi;
  scpi << ":CONF:TRAC:CHAN:NAME:ID? ";
  scpi << quote(_name);
  return std::stoi(_vna->query(scpi.str()));
}


unsigned int Trace::diagram()
{
  // CONF:TRAC:WIND? '<name>'
  std::stringstream scpi;
  scpi << ":CONF:TRAC:WIND? ";
  scpi << quote(_name);
  return std::stoi(_vna->query(scpi.str()));
}


void Trace::setDiagram(unsigned int diagram)
{
  // DISP:WIND<diagram>:TRAC:EFE '<name>'
  std::stringstream scpi;
  scpi << ":DISP:WIND" << diagram;
  scpi << ":TRAC:EFE ";
  scpi << quote(_name);
  _vna->write(scpi.str());
}


std::vector<double> Trace::y()
{
  // CALC:DATA:TRAC? '<name>',FDAT

  // get channel
  auto index   = this->channel();
  auto channel = _vna->channel(index);

  // calculate buffer size (Bytes)
  // note: requires points() scpi query
  using uint = unsigned int;
  const uint points      = channel.points();
  const uint bytes_per_point = 8;
  const uint payload     = points * bytes_per_point;
  const uint header      = 2 + uint(std::to_string(payload).size());
  const uint buffer_size = header + payload;

  // set binary data format
  PreserveDataFormat preserve_data_format(_vna);
  DataFormat format = _vna->dataFormat();
  format.setBinary64Bit();
  format.setLittleEndian();

  // scpi
  std::stringstream scpi;
  scpi << ":CALC:DATA:TRAC? ";
  scpi << quote(name());
  scpi << ",FDAT";

  // query data
  scpi::BlockData data = _vna->queryBlockData(scpi.str(), buffer_size + 1);
  if (!data.isComplete())
  {
    // query failed
    return std::vector<double>();
  }

  // parse
  return toVector<double>(data.payload(), data.payloadSize_B());
}


std::vector<std::complex<double>> Trace::y_complex()
{
  // get channel
  Channel channel = _vna->channel(this->channel());

  // calculate buffer size (Bytes)
  // note: requires points() scpi query
  using uint = unsigned int;
  const uint points      = channel.points();
  const uint bytes_per_point = 16;
  const uint payload     = points * bytes_per_point;
  const uint header      = 2 + uint(std::to_string(payload).size());
  const uint buffer_size = header + payload;

  // set binary data format
  PreserveDataFormat preserve_data_format(_vna);
  DataFormat format = _vna->dataFormat();
  format.setBinary64Bit();
  format.setLittleEndian();

  // CALC:DATA:TRAC? '<name>',FDAT
  std::stringstream scpi;
  scpi << ":CALC:DATA:TRAC? ";
  scpi << quote(name());
  scpi << ",SDAT";

  // query data
  scpi::BlockData data = _vna->queryBlockData(scpi.str(), buffer_size + 1);
  if (!data.isComplete())
  {
    // query failed
    return std::vector<std::complex<double>>();
  }

  // parse
  return toVectorComplexDouble(data.payload(), data.payloadSize_B());
}
