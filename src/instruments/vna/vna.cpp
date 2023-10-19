/**
 * \file znx.cpp
 * \brief rohdeschwarz::instruments::vna::Vna implementation
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


Display Vna::display()
{
  return Display(this);
}


DataFormat Vna::dataFormat()
{
  return DataFormat(this);
}


bool Vna::isChannel(unsigned int index)
{
  const std::vector<unsigned int> channels = this->channels();
  auto i = std::find(channels.begin(), channels.end(), index);
  return i != channels.end();
}


Channel Vna::createChannel(unsigned int index)
{
  write(":CONF:CHAN%1% 1", index);
  return channel(index);
}


Channel Vna::channel(unsigned int index)
{
  return Channel(this, index);
}


std::vector<unsigned int> Vna::channels()
{
  // CONF:CHAN:CAT?
  const std::string response = query(":CONF:CHAN:CAT?");
  const std::string csvList  = unquote(rightTrim(response));
  const std::vector<IndexName> index_names = IndexName::parse(csvList);
  return IndexName::indexesFrom(index_names);
}


bool Vna::isTrace(const char* name)
{
  const std::string name_str(name);
  return isTrace(name_str);
}


bool Vna::isTrace(const std::string& name)
{
  const std::vector<std::string> traces = this->traces();
  auto i = std::find(traces.begin(), traces.end(), name);
  return i != traces.end();
}


Trace Vna::createTrace(const char* name, unsigned int channel)
{
  const std::string name_str(name);
  return createTrace(name_str, channel);
}


Trace Vna::createTrace(const std::string& name, unsigned int channel)
{
  write(":CALC%1%:PAR:SDEF \'%2%\',\'S21\'", channel, name);
  return trace(name);
}


Trace Vna::trace(const char* name)
{
  const std::string name_str(name);
  return trace(name_str);
}


Trace Vna::trace(const std::string& name)
{
  return Trace(this, name);
}


std::vector<std::string> Vna::traces()
{
  // CONF:TRAC:CAT?
  const std::string response = query(":CONF:TRAC:CAT?");
  const std::string csvList  = unquote(rightTrim(response));
  const std::vector<IndexName> index_names = IndexName::parse(csvList);
  return IndexName::namesFrom(index_names);
}
