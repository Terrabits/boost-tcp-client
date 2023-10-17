#ifndef ROHDESCHWARZ_TO_VALUE_HPP
#define ROHDESCHWARZ_TO_VALUE_HPP


// rohdeschwarz
#include "rohdeschwarz/helpers.hpp"


// std lib
#include <string>


namespace rohdeschwarz
{


// definition
template <class OutputType>
OutputType to_value(std::string input);


// specializations


// int
template<>
int to_value(std::string input)
{
  return std::stoi(input);
};


// unsigned int
template<>
unsigned int to_value(std::string input)
{
  return std::stoul(input);
};


// double
template<>
double to_value(std::string input)
{
  return std::stod(input);
};


// string
template<>
std::string to_value(std::string input)
{
  return unquote(trim(input));
}


}       // rohdeschwarz
#endif  // ROHDESCHWARZ_TO_VALUE_HPP
