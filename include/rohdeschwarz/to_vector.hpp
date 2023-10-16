/**
 * \file to_vector.hpp
 * \brief rohdeschwarz::toVector(), rohdeschwarz::toVectorComplexDouble()
 * definitions and implementations
 */


#ifndef ROHDESCHWARZ_TO_VECTOR_HPP
#define ROHDESCHWARZ_TO_VECTOR_HPP


// std lib
#include <complex>
#include <cstddef>
#include <vector>


namespace rohdeschwarz
{


  /**
   * \brief Converts a vector of a primitive type to a vector of a different
   * primitive type.
   */
  template <class out_type, class in_type = unsigned char>
  std::vector<out_type> toVector(in_type* data, std::size_t data_size)
  {
    // out pointer type
    using out_type_p = out_type*;

    // calculate output size
    // note: integer math is automatically floored
    const std::size_t size = sizeof(in_type) * data_size / sizeof(out_type);

    // return vector copy
    const out_type_p begin = out_type_p(data);
    const out_type_p end   = begin + size;
    return std::vector<out_type>(begin, end);
  }


  /**
   * \brief Converts a vector of a primitive type to a vector of complex<double>
   *
   * The original vector is assumed to be of the format:
   *
   * `<real1><imag1><real2><imag2>...`
   */
  template <class in_type = unsigned char>
  std::vector<std::complex<double>> toVectorComplexDouble(in_type* data, std::size_t data_size)
  {
    // parse to double
    std::vector<double> values = toVector<double>(data, data_size);

    // reserve output
    std::vector<std::complex<double>> output;
    output.reserve(values.size() / 2);

    // populate
    for (int i = 0; i + 1 < values.size(); i += 2)
    {
      const double real = values[i];
      const double imag = values[i + 1];
      output.emplace_back(real, imag);
    }
    return output;
  }


}       // rohdeschwarz
#endif  // ROHDESCHWARZ_TO_VECTOR_HPP
