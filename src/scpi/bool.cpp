/**
 * \file bool.cpp
 * \brief rohdeschwarz::scpi::toBool(), rohdeschwarz::scpi::toScpi() implementations
 */


// rohdeschwarz
#include "rohdeschwarz/scpi/bool.hpp"
#include "rohdeschwarz/helpers.hpp"


std::string rohdeschwarz::scpi::toScpi(bool value)
{
  return value? "1" : "0";
}


bool rohdeschwarz::scpi::toBool(std::string scpi)
{
  return rohdeschwarz::trim(scpi) == "1";
}
