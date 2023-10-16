/**
 * \file  address.hpp
 * \brief rohdeschwarz::Address class definition
 */
#ifndef ROHDESCHWARZ_BUSSES_SOCKET_ADDRESS_HPP
#define ROHDESCHWARZ_BUSSES_SOCKET_ADDRESS_HPP


// std lib
#include <string>


// boost
#include <boost/asio.hpp>


namespace rohdeschwarz::busses::socket
{


/**
 * \brief A class for resolving boost::asio TCP IP endpoints from host, port
 */
class Address
{

public:


  /**
   * \brief Constructor
   *
   * \param[in] host host name or address
   * \param[in] port port number
   */
  Address(std::string host, int port);


  /**
   * \brief host or address
   */
  std::string host() const;


  /**
   * \brief port number
   */
  int port() const;


  // resolve

  /**
   * \brief Resolves TCP IP endpoint(s) from host, port
   *
   * \param[in] io_context IO Context for scheduling resolve()
   * \returns   A non-empty list if endpoints could be resolved; an empty list otherwise
   */
  boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type resolve(boost::asio::io_context& io_context) const;


private:

  std::string _host;
  int         _port;


};  // class Address


}       // namespace rohdeschwarz::busses::socket
#endif  // ROHDESCHWARZ_BUSSES_SOCKET_ADDRESS_HPP
