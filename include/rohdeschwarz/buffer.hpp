#ifndef ROHDESCHWARZ_BUFFER_HPP
#define ROHDESCHWARZ_BUFFER_HPP


// std lib
#include <cstddef>
#include <memory>


namespace RohdeSchwarz
{


class Buffer
{

public:


  // constructor / destructor

  Buffer(std::size_t size);

  ~Buffer();


  // size

  std::size_t size() const;

  void setSize(std::size_t size);


  // contents

  char* data();

  const char* data() const;


private:

  std::size_t _size;
  std::unique_ptr<char[]> _buffer;


};


}       // namespace RohdeSchwarz
#endif  // ROHDESCHWARZ_BUFFER_HPP
