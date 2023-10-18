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
  return std::stoi(trim(input));
};


// unsigned int
template<>
unsigned int to_value(std::string input)
{
  return std::stoul(trim(input));
};


// double
template<>
double to_value(std::string input)
{
  return std::stod(trim(input));
};


// string
template<>
std::string to_value(std::string input)
{
  return unquote(trim(input));
}


}       // rohdeschwarz
#endif  // ROHDESCHWARZ_TO_VALUE_HPP
