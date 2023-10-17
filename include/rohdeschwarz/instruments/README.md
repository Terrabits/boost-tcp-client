# Instruments

TODO:

-   Add `Bus`, `Visa` support to `Instrument`
-   Add io formatting, return value


## IO Formatting, Return Value

```c++
#include "boost/format.hpp"
#include <string>


template<class... Args>
bool write(std::string format, Args&&... args)
{
  // interpolate
  auto boost_format = boost::format(format);
  ([&]
  {
    boost_format % args;
  } (), ...);

  // write
  return write(boost_format.str());
}


template<class... Args>
std::string query(std::string format, Args&&... args)
{
  // write
  if (!write(format, &args...))
  {
    // error
    return std::string();
  }

  // return results
  return read();
}


// basic scpi with formatting and return type conversion

template<class OutputType>
OutputType readValue()
{
  return to_value<OutputType>(read());
}

template<class OutputType, class... Args>
OutputType queryValue(std::string format, Args&&... args)
{
  // write
  if (!write(format, &args...))
  {
    // error
    return OutputType();
  }

  // return results
  return readValue<OutputType>();
}

```
