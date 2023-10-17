/**
 * \file bool.cpp
 * \brief rohdeschwarz::scpi::toBool(), rohdeschwarz::scpi::toScpi() implementations
 */


// rohdeschwarz
#include "rohdeschwarz/scpi/bool.hpp"
#include "rohdeschwarz/helpers.hpp"
using namespace rohdeschwarz::scpi;
using namespace rohdeschwarz;


std::string toScpi(bool value)
{
  return value? "1" : "0";
}


bool toBool(const std::string& scpi)
{
  return trim(scpi) == "1";
}
