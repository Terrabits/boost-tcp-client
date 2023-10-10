/**
 * \file data_format.hpp
 * \brief RsVisa::DataFormat definition
 */


#ifndef RS_VISA_DATA_FORMAT_HPP
#define RS_VISA_DATA_FORMAT_HPP


// std lib
#include <string>


namespace RsVisa
{

// forward declare Znx
class Znx;


/**
 * \brief Object-oriented control of the data transfer format and byte order
 *
 * There are three possible data transfer formats:
 * - ASCII
 * - 32-bit float
 * - 64-bit float (i.e. `double`)
 *
 * For floats, the possible Byte Orders are:
 * - Little-endian (e.g. x86, x86_64)
 * - Big-endian (e.g. PowerPC)
 */
class DataFormat
{

public:

  // life cycle

  /**
   * \brief Constructor
   *
   * \param[in] znx Pointer to underlying `Znx` instance
   */
  DataFormat(Znx* znx);


  // ascii

  /**
   * \brief Queries if data transfer format is ASCII
   */
  bool isAscii();


  /**
   * \brief Sets data transfer format to ASCII
   *
   * ASCII data is equivalent to CSV format
   */
  void setAscii();


  // binary 32 bit

  /**
   * \brief Queries if data transfer format is 32-bit float
   */
  bool isBinary32Bit();


  /**
   * \brief Sets data transfer format to 32-bit float
   *
   * Data is transferred as 32-bit (4 byte) floating point values
   * with no separator. In C/C++, this corresponds to type `float`.
   */
  void setBinary32Bit();


  // binary 64 bit

  /**
   * \brief Queries if data transfer format is 64-bit float
   */
  bool isBinary64Bit();


  /**
   * \brief Sets data transfer format to 64-bit float
   *
   * Data is transferred as 64-bit (8 byte) floating point values
   * with no separator. In C/C++, this corresponds to type `double`.
   */
  void setBinary64Bit();


  // big endian

  /**
   * \brief Queries if the byte order for float data transfer is big-endian
   */
  bool isBigEndian();


  /**
   * \brief Sets the byte order for float data transfer to big-endian
   */
  void setBigEndian();


  // little endian

  /**
   * \brief Queries if the byte order for float data transfer is little-endian
   */
  bool isLittleEndian();


  /**
   * \brief Sets the byte order for float data transfer to little-endian
   */
  void setLittleEndian();

private:

  Znx* _znx;


  // helpers

  /**
   * \brief Queries data transfer format
   *
   * Uses SCPI query `FORM?`
   */
  std::string dataFormat();


  /**
   * \brief Queries byte order for data transfer
   *
   * Uses SCPI query `FORM:BORD?"`
   */
  std::string byteOrder();


};  // class DataFormat


}       // namespace RsVisa
#endif  // RS_VISA_DATA_FORMAT_HPP
