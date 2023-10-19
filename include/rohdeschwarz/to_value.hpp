#ifndef ROHDESCHWARZ_TO_VALUE_HPP
#define ROHDESCHWARZ_TO_VALUE_HPP


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
int to_value(std::string input);


// unsigned int
template<>
unsigned int to_value(std::string input);


// double
template<>
double to_value(std::string input);


// string
template<>
std::string to_value(std::string input);


}       // rohdeschwarz
#endif  // ROHDESCHWARZ_TO_VALUE_HPP
