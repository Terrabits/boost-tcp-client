/**
 * \file  main.cpp
 * \brief rohdeschwarz::busses::socket::Socket example
 *
 * This example demonstrates basic use of the `rohdeschwarz::busses::socket::Socket` class.
 *
 * \include main.cpp
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/socket.hpp"
using Socket = rohdeschwarz::busses::socket::Socket;


// std lib
#include <iostream>
#include <string>


// constants
const char* HOST = "localhost";
const int   PORT = 5025;


int main()
{
  // create open socket
  Socket socket(HOST, PORT);

  // print instrument id string
  std::cout << socket.query("*IDN?\n");
  return 0;
}
