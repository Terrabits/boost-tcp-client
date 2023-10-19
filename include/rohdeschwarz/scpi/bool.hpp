/**
 * \file bool.cpp
 * \brief rohdeschwarz::scpi::toBool(), rohdeschwarz::scpi::toScpi() declarations
 */


#ifndef ROHDESCHWARZ_SCPI_BOOL_HPP
#define ROHDESCHWARZ_SCPI_BOOL_HPP


// std lib
#include <string>


namespace rohdeschwarz::scpi
{


/**
 * \brief Converts C/C++ `bool` to SCPI bool
 *
 * \returns `"1"` if `value` is `true`; `"0"` otherwise
 */
std::string toScpi(bool value);


/**
 * \brief Converts SCPI bool to C/C++ bool
 *
 * \returns `true` if `scpi` is `"1"`; `false` otherwise
 */
bool toBool(std::string scpi);


}       // namespace rohdeschwarz::scpi
#endif  // ROHDESCHWARZ_SCPI_BOOL_HPP
