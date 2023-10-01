/**
 * \file  address.hpp
 * \brief RohdeSchwarz::Address class definition
 */
#ifndef ROHDESCHWARZ_ADDRESS_HPP
#define ROHDESCHWARZ_ADDRESS_HPP


// std lib
#include <string>


// boost
#include <boost/asio.hpp>


namespace RohdeSchwarz
{


/**
 * \brief A convenience class for calling
 *   `boost::asio::ip::tcp::resolver::resolve()`
 */
class Address
{

public:


  // constructor

  Address(std::string host, int port);


  // host, port

  std::string host() const;

  int port() const;


  // resolve

  /**
   * /brief Resolves TCP IP endpoint(s) from host, port
   *
   * \param[in] io_context IO Context for scheduling resolution
   * \returns   TCPIP endpoint(s)
   */
  boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type resolve(boost::asio::io_context& io_context) const;


private:

  std::string _host;
  int         _port;


};  // class Address


}       // namespace RohdeSchwarz
#endif  // ROHDESCHWARZ_ADDRESS_HPP
