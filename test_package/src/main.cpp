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
using system_error = rohdeschwarz::busses::socket::system_error;
using Instrument   = rohdeschwarz::instruments::Instrument;


int main()
{
  try
  {
    // query id string
    Instrument instrument;
    instrument.openTcp("localhost");
    instrument.id();
  }

  // error?
  catch (system_error& e)
  {
    // ignore
  }
  return 0;
}
