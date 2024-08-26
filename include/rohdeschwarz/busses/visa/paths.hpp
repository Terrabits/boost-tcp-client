#ifndef ROHDESCHWARZ_BUSSES_VISA_PATHS_HPP
#define ROHDESCHWARZ_BUSSES_VISA_PATHS_HPP


// std lib
#include <string>
#include <vector>


// boost
#include "boost/predef.h"


namespace rohdeschwarz::busses::visa
{


#if   BOOST_OS_WINDOWS

/**
 * \brief windows; visa shared library is in path
 *
 * The VISA shared libraries are installed to the following paths on Windows:
 *
 * - `C:\Windows\system32\visa64.dll`
 * - `C:\Windows\system32\visa32.dll`
 *
 * Since `C:\Windows\system32` is always in path, the full path is not required.
 */
const std::vector<std::string> VISA_PATHS
{
  "visa64.dll",
  "visa32.dll"
};


#elif BOOST_OS_MACOS

/**
 * \brief macos rohde & schwarz visa shared library path
 */
const std::vector<std::string> VISA_PATHS
{
  "/Library/Frameworks/RsVisa.framework/Versions/Current/RsVisa/librsvisa.dylib"
};


#elif BOOST_OS_LINUX

/**
 * \brief linux visa shared library path
 */
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
