/**
 * \file znx.cpp
 * \brief rohdeschwarz::instruments::vna::Znx implementation
 */


// rohdeschwarz
#include "rohdeschwarz/instruments/vna/vna.hpp"
#include "rohdeschwarz/scpi/index_name.hpp"
#include "rohdeschwarz/helpers.hpp"
using namespace rohdeschwarz::instruments::vna;
using namespace rohdeschwarz::scpi;
using namespace rohdeschwarz;


// std lib
#include <algorithm>
#include <sstream>


// constants
const unsigned int _11_kB_ = 11 * 1024;
const unsigned int _12_kB_ = 12 * 1024;


Display Znx::display()
{
  return Display(this);
}


DataFormat Znx::dataFormat()
{
  return DataFormat(this);
}


bool Znx::isChannel(unsigned int index)
{
  const std::vector<unsigned int> channels = this->channels();
  auto i = std::find(channels.begin(), channels.end(), index);
  return i != channels.end();
}


Channel Znx::createChannel(unsigned int index)
{
  // CONF:CHAN<Ch> 1
  std::stringstream scpi;
  scpi << ":CONF:CHAN" << index << " 1";
  write(scpi.str());

  return channel(index);
}


Channel Znx::channel(unsigned int index)
{
  return Channel(this, index);
}


std::vector<unsigned int> Znx::channels()
{
  // CONF:CHAN:CAT?
  const std::string response = query(":CONF:CHAN:CAT?", _11_kB_);
  const std::string csvList  = unquote(rightTrim(response));
  const std::vector<IndexName> index_names = IndexName::parse(csvList);
  return IndexName::indexesFrom(index_names);
}


bool Znx::isTrace(const char* name)
{
  const std::string name_str(name);
  return isTrace(name_str);
}


bool Znx::isTrace(const std::string& name)
{
  const std::vector<std::string> traces = this->traces();
  auto i = std::find(traces.begin(), traces.end(), name);
  return i != traces.end();
}


Trace Znx::createTrace(const char* name, unsigned int channel)
{
  const std::string name_str(name);
  return createTrace(name_str, channel);
}


Trace Znx::createTrace(const std::string& name, unsigned int channel)
{
  // CALC<Ch>:PAR:SDEF '<name>','S21'
  std::stringstream scpi;
  scpi << ":CALC" << channel;
  scpi << ":PAR:SDEF ";
  scpi << quote(name);
  scpi << "," << quote("S21");
  write(scpi.str());

  return trace(name);
}


Trace Znx::trace(const char* name)
{
  const std::string name_str(name);
  return trace(name_str);
}


Trace Znx::trace(const std::string& name)
{
  return Trace(this, name);
}


std::vector<std::string> Znx::traces()
{
  // CONF:TRAC:CAT?
  const std::string response = query(":CONF:TRAC:CAT?", _12_kB_);
  const std::string csvList  = unquote(rightTrim(response));
  const std::vector<IndexName> index_names = IndexName::parse(csvList);
  return IndexName::namesFrom(index_names);
}
