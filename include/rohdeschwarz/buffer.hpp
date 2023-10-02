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
 * \brief A convenience class for boost::asio::buffer()
 *
 * The RohdeSchwarz::Buffer class manages a resizable `char[]` array and
 * generates `boost::asio` `const_buffer` and `mutable_buffer` objects for use
 # in IO operations.
 */
class Buffer
{

public:


  /**
   * \brief Constructor
   *
   * Constructs a buffer object with the specified size
   *
   * \param[in] size Size of the `char[]` buffer.
   */
  Buffer(std::size_t size);


  /**
   * \brief Buffer size
   */
  std::size_t size() const;


  /**
   * \brief Resize the buffer
   *
   * Resizes the internal `char[]` buffer.
   *
   * \param[in] size New buffer size
   *
   * \note The current buffer is destroyed. All pointers and boost buffers are
   *       invalidated.
   */
  void resize(std::size_t size);


  /**
   * \brief Returns a pointer to the buffer data
   *
   * \note Calls to Buffer::resize() will invalidate this pointer.
   */
  char* data();


  /**
   * \brief Returns a const pointer to the buffer data
   *
   * \note Calls to Buffer::resize() will invalidate this pointer.
   */
  const char* data() const;


  /**
   * \brief Converts the contents of the buffer to a `std::string`
   *
   * \note Buffer contents must be a null-terminated c string.
   */
  std::string toString() const;


  /**
   * \brief Converts the first `size` characters in the buffer to
   * `std::string`
   */
  std::string toString(std::size_t size_B) const;


  /**
   * \brief Returns a mutable buffer for use with `boost::asio`
   *
   * `mutable_buffer` is a `char[]` view required by `boost::asio::read()`.
   *
   * \note Calls to Buffer::resize() will invalidate this pointer.
   */
  boost::asio::mutable_buffer toMutableBuffer();


  /**
   * \brief Returns a const buffer for use with `boost::asio`
   *
   * `const_buffer` is a `char[]` view required by `boost::asio::write()`.
   *
   * \note Calls to Buffer::resize() will invalidate this pointer.
   */
  boost::asio::const_buffer toConstBuffer() const;


private:

  std::vector<char> _buffer;


};  // class Buffer


}       // namespace RohdeSchwarz
#endif  // ROHDESCHWARZ_BUFFER_HPP
