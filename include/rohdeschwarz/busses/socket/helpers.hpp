/**
 * \file  helpers.hpp
 * \brief rohdeschwarz::busses::socket helper function definitions
 */
#ifndef ROHDESCHWARZ_BUSSES_SOCKET_HELPERS_HPP
#define ROHDESCHWARZ_BUSSES_SOCKET_HELPERS_HPP


// rohdeschwarz
#include "rohdeschwarz/busses/bus.hpp"


// boost
#include <boost/asio.hpp>


namespace rohdeschwarz::busses::socket
{


/**
 * \brief Resolves TCP IP endpoint(s) from host, port
 *
 * \param[in] host       Host name or IP address
 * \param[in] port       TCP port
 * \param[in] io_context IO Context for scheduling resolve()
 * \returns   A non-empty list if endpoints could be resolved; an empty list otherwise
 */
boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type resolve
(
  const std::string &host,
  int port,
  boost::asio::io_context& io_context
);


}       // rohdeschwarz::busses::socket
#endif  // ROHDESCHWARZ_BUSSES_SOCKET_HELPERS_HPP
