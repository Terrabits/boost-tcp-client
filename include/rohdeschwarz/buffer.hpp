/**
 * \file  buffer.hpp
 * \brief RohdeSchwarz::Buffer class definition
 */
#ifndef ROHDESCHWARZ_BUFFER_HPP
#define ROHDESCHWARZ_BUFFER_HPP


// std lib
#include <cstddef>
#include <string>
#include <vector>


// boost
#include <boost/asio.hpp>


namespace RohdeSchwarz
{


/**
 * \brief A managed `char[]` buffer for use with `boost::asio`
 */
class Buffer
{

public:


  // constructor / destructor

  Buffer(std::size_t size);


  // size

  std::size_t size() const;

  void resize(std::size_t size);


  // data

  char* data();

  const char* data() const;


  // to string

  std::string toString() const;

  std::string toString(std::size_t size_B) const;


  // to boost buffer

  boost::asio::mutable_buffer toMutableBuffer();

  boost::asio::const_buffer toConstBuffer() const;


private:

  std::vector<char> _buffer;


};  // class Buffer


}       // namespace RohdeSchwarz
#endif  // ROHDESCHWARZ_BUFFER_HPP
