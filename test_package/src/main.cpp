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
using system_error = rohdeschwarz::busses::socket::system_error;
using Socket       = rohdeschwarz::busses::socket::Socket;


// std lib
#include <iostream>


int main()
{
  try
  {
    // create open socket
    Socket socket("localhost", 5025);

    // get instrument id
    socket.query("*IDN?\n");
  }
  catch (system_error& e)
  {
    // ignore error
  }
  return 0;
}
