/**
 * \file  bus.hpp
 * \brief rohdeschwarz::busses::Bus class definition
 */
#ifndef ROHDESCHWARZ_BUSSES_BUS_HPP
#define ROHDESCHWARZ_BUSSES_BUS_HPP


// std lib
#include <cstddef>
#include <string>


namespace rohdeschwarz::busses
{


class Bus
{

public:


  /**
   * \brief Constructor
   */
  Bus();


  /**
   * \brief Destructor
   *
   * The destructor should be implemented by subclasses to close the connection,
   * if necessary.
   */
  virtual ~Bus();


  // pure virtual end point
  virtual std::string endpoint() const = 0;


  // buffer
  unsigned char* data();
  const unsigned char* data() const;


  // buffer size
  std::size_t bufferSize_B() const;
  void setBufferSize(std::size_t bytes);


  // raw io with external buffer; pure virtual
  virtual bool readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize = nullptr) = 0;
  virtual bool writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize = nullptr) = 0;


  // raw io with internal buffer
  bool readData(std::size_t* readSize = nullptr);


  // std::string io
  std::string read();
  bool write(const std::string& scpi);
  std::string query(const std::string& scpi);


  // c string io
  bool write(const char* scpi);
  bool write(const char* scpi, std::size_t size);

  std::string query(const char* scpi);
  std::string query(const char* scpi, std::size_t size);


private:

  std::vector<unsigned char> _buffer;


};  // class Bus


}       // rohdeschwarz::busses
#endif  // ROHDESCHWARZ_BUSSES_BUS_HPP
