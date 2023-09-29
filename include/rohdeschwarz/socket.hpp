#ifndef ROHDESCHWARZ_SOCKET_HPP
#define ROHDESCHWARZ_SOCKET_HPP


// rohdeschwarz
#include "rohdeschwarz/buffer.hpp"


// boost
#include <boost/asio.hpp>


// std lib
#include <cstddef>
#include <memory>
#include <string>


namespace RohdeSchwarz
{


// exceptions
using system_error = boost::system::system_error;


class Socket
{

public:


  // constructors / destructor

  Socket(const char* address, int port = 5025);
  Socket(const std::string& address, int port = 5025);
  ~Socket();


  // address

  std::string address() const;


  // port

  int port() const;


  // read buffer

  std::size_t bufferSize_B() const;

  void setBufferSize(std::size_t bufferSize_B);


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

  // address, port
  std::string _address;
  int         _port;


  // socket
  boost::asio::io_context _io_context;
  boost::asio::ip::tcp::socket _socket;


  // buffer
  Buffer _buffer;


  // asio buffers

  boost::asio::mutable_buffer getBuffer();

  static boost::asio::mutable_buffer getBuffer(Buffer& buffer);

  static boost::asio::mutable_buffer getBuffer(char* buffer, std::size_t bufferSize_B);

  static boost::asio::const_buffer getBuffer(const char* buffer, std::size_t bufferSize_B);


  // helpers
  boost::asio::ip::basic_resolver<boost::asio::ip::tcp>::results_type resolve_endpoints();

  bool open();

  void close();


};  // class Socket


}       // namespace RohdeSchwarz
#endif  // ROHDESCHWARZ_SOCKET_HPP
