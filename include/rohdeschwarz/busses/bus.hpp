/**
 * \file  bus.hpp
 * \brief rohdeschwarz::busses::Bus class definition
 */
#ifndef ROHDESCHWARZ_BUSSES_BUS_HPP
#define ROHDESCHWARZ_BUSSES_BUS_HPP


// std lib
#include <cstddef>
#include <string>
#include <vector>


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


  // timeout
  virtual int timeout_ms() const = 0;
  virtual bool setTimeout(int timeout_ms) = 0;


  // buffer size
  std::size_t bufferSize_B() const;
  void setBufferSize(std::size_t bytes);


  // buffer
  std::vector<unsigned char>* buffer();
  const std::vector<unsigned char>* buffer() const;
  std::vector<unsigned char> takeData();


  // raw io; pure virtual
  virtual bool readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize = nullptr) = 0;
  virtual bool writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize = nullptr) = 0;


  // raw io with internal buffer
  bool readData(std::size_t* readSize = nullptr);


  // status
  virtual bool isError() const = 0;
  virtual std::string statusMessage() const = 0;


private:

  std::vector<unsigned char> _buffer;


};  // class Bus


}       // rohdeschwarz::busses
#endif  // ROHDESCHWARZ_BUSSES_BUS_HPP
