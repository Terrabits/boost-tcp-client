/**
 * \file  socket.cpp
 * \brief RohdeSchwarz::Socket example
 *
 * This example demonstrates basic use of the `RohdeSchwarz::Socket` class.
 *
 * \include socket.cpp
 */


// rohdeschwarz
#include "rohdeschwarz/socket.hpp"
using namespace RohdeSchwarz;


// std lib
#include <iostream>
#include <sstream>
#include <string>


int main(int argc, char* argv[])
{

  // check args
  if (argc != 2)
  {
    std::cerr << "Usage: http-get <host>\n";
    return 1;
  }


  try
  {
    // create socket; connect
    Socket socket(argv[1], 80);


    // create http get header
    std::stringstream header;
    header << "GET / HTTP/1.1\r\nHost: ";
    header << argv[1];
    header << ":80\r\n\r\n";


    // make request; print response
    std::string response = socket.query(header.str());
    std::cout << response << std::endl << std::endl;


  }


  catch (std::exception& e)
  {

    std::cerr << "Exception: " << e.what() << "\n";
    return 2;

  }


  // success
  return 0;
}
