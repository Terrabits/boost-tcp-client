/**
 * \file  main.cpp
 * \brief conan test package source
 *
 * This source file is part of a conan test package for `rohdeschwarz`
 *
 * \include main.cpp
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/socket.hpp"
#include "rohdeschwarz/instruments/instrument.hpp"
#include "rohdeschwarz/helpers.hpp"
using system_error = rohdeschwarz::busses::socket::system_error;
using Instrument   = rohdeschwarz::instruments::Instrument;


// std lib
#include <iostream>


int main()
{

// connect to instrument
Instrument instrument;
if (instrument.openTcp("localhost"))
{
  // connected

  // get id
  const auto id = rohdeschwarz::trim(instrument.id());

  // print for debug
  #ifndef NDEBUG
    std::cout << "connected: " << id << std::endl;
  #endif

}
else
{
  // connection failed

  // print for debug
  #ifndef NDEBUG
    std::cout << "error: connection to localhost failed" << std::endl;
  #endif

}
return 0;


}  // main
