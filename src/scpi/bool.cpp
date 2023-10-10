/**
 * \file bool.cpp
 * \brief RsVisa::toBool(), RsVisa::toScpi() implementations
 */


#include "bool.hpp"


// RsVisa
#include "helpers.hpp"


std::string RsVisa::toScpi(bool value)
{
  return value? "1" : "0";
}


bool RsVisa::toBool(const std::string& scpi)
{
  return trim(scpi) == "1";
}
