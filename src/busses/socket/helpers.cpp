/**
 * \file  helpers.cpp
 * \brief rohdeschwarz::busses::socket helper function implementations
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/helpers.hpp"
// using namespace rohdeschwarz::busses::socket;


// implementation

boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type
  rohdeschwarz::busses::socket::resolve
(
  const std::string &host,
  int port,
  boost::asio::io_context& io_context
)
{
  // get port string
  std::string port_str = std::to_string(port);

  // resolve endpoint(s)
  boost::asio::ip::tcp::resolver resolver(io_context);
  return resolver.resolve(host.c_str(), port_str.c_str());
}
