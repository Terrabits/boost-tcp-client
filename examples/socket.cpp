/**
 * \file  socket.cpp
 * \brief rohdeschwarz::Socket example
 *
 * This example demonstrates basic use of the `rohdeschwarz::Socket` class.
 *
 * \include socket.cpp
 */


// rohdeschwarz
#include "rohdeschwarz/busses/socket/socket.hpp"
using namespace rohdeschwarz::busses::socket;


// std lib
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{

  // check args
  if (argc != 2)
  {
    std::cerr << "Usage: `socket-example <host>`" << std::endl;
    std::cerr << "Connects to the instrument at <host> and prints the id string" << std::endl;
    return 1;
  }


  // get host argument
  auto host = argv[1];


  try
  {
    // create open socket
    Socket socket(host, 5025);

    // print instrument id string
    std::cout << socket.query("*IDN?\n");
  }

  
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 2;
  }


  // success
  return 0;
}
