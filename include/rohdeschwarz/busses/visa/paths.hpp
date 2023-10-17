#ifndef ROHDESCHWARZ_BUSSES_VISA_PATHS_HPP
#define ROHDESCHWARZ_BUSSES_VISA_PATHS_HPP


// std lib
#include <string>
#include <vector>


// boost
#include "boost/predef.h"


namespace rohdeschwarz::busses::visa
{


// define visa paths for current os


#if   BOOST_OS_WINDOWS

// notes:
//   - On windows visa is in path and can be loaded by filename
//   - try 64 bit dll first; if this fails, try 32 bit
const std::vector<std::string> VISA_PATHS
{
  "visa64.dll",
  "visa32.dll"
};


#elif BOOST_OS_MACOS

const std::vector<std::string> VISA_PATHS
{
  "/Library/Frameworks/RsVisa.framework/Versions/Current/RsVisa/librsvisa.dylib"
};


#elif BOOST_OS_LINUX

const std::vector<std::string> VISA_PATHS
{
  "/usr/local/bin/libvisa.so"
};


#else

// operating system is not supported
# error operating system is not supported; only windows, macos, and linux are supported


#endif  //


}       // rohdeschwarz::busses::visa
#endif  // ROHDESCHWARZ_BUSSES_VISA_PATHS_HPP
