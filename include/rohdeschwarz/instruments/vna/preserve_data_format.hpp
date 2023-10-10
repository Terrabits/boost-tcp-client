/**
* \file preserve_data_format.hpp
* \brief RsVisa::PreserveDataFormat definition
 */


#ifndef RS_VISA_PRESERVE_DATA_FORMAT
#define RS_VISA_PRESERVE_DATA_FORMAT


// RsVisa
#include "znx.hpp"


namespace RsVisa
{

/**
 * \brief Class for preserving data format and byte order in a particular scope
 *
 * `PreserveDataFormat` is intended for use in methods that require a
 * particular data transfer format and byte order, but want to preserve the
 * data format and byte order set by the user.
 *
 * On construction, `PreserveDataFormat` stores the current data transfer format.
 * On destruction, the data transfer format is restored.
 */
class PreserveDataFormat
{

public:

  // lifecycle

  /**
   * \brief Constructor
   *
   * Stores the current data transfer format and byte order.
   *
   * \param[in] znx Pointer to underlying `Znx` instance.
   */
  PreserveDataFormat(Znx *znx);


  /**
   * \brief Destructor
   *
   * Restores the data transfer format and byte order stored
   * during construction.
   */
  ~PreserveDataFormat();


private:

  // initial data format settings
  bool _isBinary;
  bool _is64Bit;
  bool _isBigEndian;
  DataFormat _dataFormat;


  // helpers

  /**
   * \brief Restores data transfer format stored during construction
   */
  void restoreBinaryBits();


  /**
   * \brief Restores byte order stored during construction.
   */
  void restoreByteOrder();


};  // class PreserveDataFormat


}       // namespace RsVisa
#endif  // RS_VISA_PRESERVE_DATA_FORMAT
