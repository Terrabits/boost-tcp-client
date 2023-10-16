/**
 * \file  socket.hpp
 * \brief rohdeschwarz::busses::socket::Socket class definition
 */
#ifndef ROHDESCHWARZ_BUSSES_SOCKET_SOCKET_HPP
#define ROHDESCHWARZ_BUSSES_SOCKET_SOCKET_HPP


// rohdeschwarz
#include "rohdeschwarz/busses/socket/address.hpp"
#include "rohdeschwarz/busses/socket/buffer.hpp"


// boost
#include <boost/asio.hpp>


// std lib
#include <cstddef>
#include <string>


namespace rohdeschwarz::busses::socket
{


/**
 * \brief System error exception
 *
 * This is a reference to `boost::system::system_error` provided for
 * convenience
 */
using system_error = boost::system::system_error;


/**
 * \brief A class for managing synchronous TCP IP sockets
 */
class Socket
{

public:


  /**
   * \brief Constructor
   *
   * Constructs a socket object that is connected to server `host`, `port`
   *
   * \param[in] host host or ip address
   * \param[in] port port number
   * \returns   An object with an open socket
   * \exception `boost::system::system_error` if connection fails
   */
  Socket(const char* host, int port = 5025);


  /**
   * \brief Constructor
   *
   * Constructs a socket object that is connected to server `host`, `port`
   *
   * \param[in] host host or ip address
   * \param[in] port port number
   * \returns   An object with an open socket
   * \exception `boost::system::system_error` if connection fails
   */
  Socket(const std::string& host, int port = 5025);


  /**
   * \brief Destructor
   *
   * The destructor closes the socket if it is currently open
   */
  ~Socket();


  /**
   * \brief Host or ip address
   */
  std::string host() const;


  /**
   * \brief Port number
   */
  int port() const;


  /**
   * \brief Returns the current read buffer size, in bytes
   */
  std::size_t bufferSize_B() const;


  /**
   * \brief Sets the read buffer size, in bytes
   *
   * \param[in] size_B New buffer size, in bytes
   */
  void setBufferSize(std::size_t size_B);



  /**
   * \brief Read data from socket
   *
   * \returns Data read from socket
   *
   * \note The maximum read size is determined by Socket::bufferSize_B(),
   * Socket::setBufferSize()
   */
  std::string read();


  /**
   * \brief Read at most `bufferSize_B` bytes from socket
   *
   * \param[in] bufferSize_B Maximum number of bytes to read
   * \returns   Data read from socket
   */
  std::string read(std::size_t bufferSize_B);

  /**
   * \brief Write data
   *
   * \param[in] data Null-terminated c string
   * \returns   Number of bytes written
   */
  std::size_t write(const char* data);


  /**
   * \brief Write `size` bytes from `data`
   *
   * \param[in] data `char[]` data
   * \param[in] size Number of bytes
   * \returns   Number of bytes written
   */
  std::size_t write(const char* data, std::size_t size);


  /**
   * \brief Write string data
   *
   * \param[in] data String data
   * \returns   Number of bytes written
   */
  std::size_t write(const std::string& data);


  /**
   * \brief Perform SCPI query
   *
   * \param[in] scpi Null-terminated SCPI query
   * \returns   Query response
   *
   * \note The maximum read size is determined by Socket::bufferSize_B(),
   * Socket::setBufferSize()
   */
  std::string query(const char* scpi);


  /**
   * \brief Perform SCPI query
   *
   * \param[in] scpi Null-terminated SCPI query
   * \param[in] bufferSize_B Maximum number of bytes to read
   * \returns   Query response
   */
  std::string query(const char* scpi, std::size_t bufferSize_B);


  /**
   * \brief Perform SCPI query
   *
   * \param[in] scpi SCPI query
   * \returns   Query response
   *
   * \note The maximum read size is determined by Socket::bufferSize_B(),
   * Socket::setBufferSize()
   */
  std::string query(const std::string& scpi);


  /**
   * \brief Perform SCPI query
   *
   * \param[in] scpi Null-terminated SCPI query
   * \param[in] bufferSize_B Maximum number of bytes to read
   * \returns   Query response
   */
  std::string query(const std::string& scpi, std::size_t bufferSize_B);


private:

  Address _address;
  Buffer  _buffer;
  boost::asio::io_context _io_context;
  boost::asio::ip::tcp::socket _socket;


  // helpers


  /**
   * \brief Connects to server
   */
  bool open();


  /**
   * \brief Disconnects from server
   */
  void close();


};  // class Socket


}       // namespace rohdeschwarz::busses::socket
#endif  // ROHDESCHWARZ_BUSSES_SOCKET_SOCKET_HPP
