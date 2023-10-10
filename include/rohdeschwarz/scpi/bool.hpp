/**
 * \file bool.cpp
 * \brief RsVisa::toBool(), RsVisa::toScpi() declarations
 */


#ifndef RS_VISA_BOOL_HPP
#define RS_VISA_BOOL_HPP


// std lib
#include <string>


namespace RsVisa
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
bool toBool(const std::string& scpi);


}       // namespace RsVisa
#endif  // RS_VISA_BOOL_HPP
