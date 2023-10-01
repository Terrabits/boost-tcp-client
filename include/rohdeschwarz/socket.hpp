#ifndef ROHDESCHWARZ_SOCKET_HPP
#define ROHDESCHWARZ_SOCKET_HPP


// rohdeschwarz
#include "rohdeschwarz/address.hpp"
#include "rohdeschwarz/buffer.hpp"


// boost
#include <boost/asio.hpp>


// std lib
#include <cstddef>
#include <string>


namespace RohdeSchwarz
{


// exceptions
using system_error = boost::system::system_error;


class Socket
{

public:


  // constructors / destructor

  Socket(const char* host,        int port = 5025);
  Socket(const std::string& host, int port = 5025);
  ~Socket();


  // host, port

  std::string host() const;

  int port() const;


  // buffer

  std::size_t bufferSize_B() const;

  void setBufferSize(std::size_t size_B);


  // i/o

  std::string read();

  std::string read(std::size_t bufferSize_B);

  std::size_t write(const char* data);

  std::size_t write(const char* data, std::size_t size);

  std::size_t write(const std::string& data);

  std::string query(const char* scpi);

  std::string query(const char* scpi, std::size_t bufferSize_B);

  std::string query(const std::string& scpi);

  std::string query(const std::string& scpi, std::size_t bufferSize_B);


private:

  Address _address;
  Buffer  _buffer;
  boost::asio::io_context _io_context;
  boost::asio::ip::tcp::socket _socket;


  // helpers

  bool open();

  void close();


};  // class Socket


}       // namespace RohdeSchwarz
#endif  // ROHDESCHWARZ_SOCKET_HPP
