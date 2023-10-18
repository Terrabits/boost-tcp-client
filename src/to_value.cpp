// rohdeschwarz
#include "rohdeschwarz/helpers.hpp"
#include "rohdeschwarz/to_value.hpp"


template<>
int rohdeschwarz::to_value(std::string input)
{
  return std::stoi( rohdeschwarz::trim(input));
}


// unsigned int
template<>
unsigned int rohdeschwarz::to_value(std::string input)
{
  return std::stoul( rohdeschwarz::trim(input));
}


// double
template<>
double rohdeschwarz::to_value(std::string input)
{
  return std::stod( rohdeschwarz::trim(input));
}


// string
template<>
std::string rohdeschwarz::to_value(std::string input)
{
  return rohdeschwarz::unquote( rohdeschwarz::trim(input));
}
