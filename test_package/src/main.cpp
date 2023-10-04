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
