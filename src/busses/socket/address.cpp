/**
 * \file  address.cpp
 * \brief rohdeschwarz::Address class implementation
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/address.hpp"
using namespace rohdeschwarz::busses::socket;


Address::Address(std::string host, int port) :
  _host(host),
  _port(port)
{
  // pass
}


std::string Address::host() const
{
  return _host;
}


int Address::port() const
{
  return _port;
}


boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type Address::resolve(boost::asio::io_context& io_context) const
{
  // get port string
  std::string port = std::to_string(_port);

  // resolve endpoint(s)
  boost::asio::ip::tcp::resolver resolver(io_context);
  return resolver.resolve(_host.c_str(), port.c_str());
}
