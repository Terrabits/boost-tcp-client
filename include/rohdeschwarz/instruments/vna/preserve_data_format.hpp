/**
* \file preserve_data_format.hpp
* \brief rohdeschwarz::instruments::vna::PreserveDataFormat definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_VNA_PRESERVE_DATA_FORMAT_HPP
#define ROHDESCHWARZ_INSTRUMENTS_VNA_PRESERVE_DATA_FORMAT_HPP


// rohdeschwarz
#include "rohdeschwarz/instruments/vna/vna.hpp"


namespace rohdeschwarz::instruments::vna
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
   * \param[in] vna Pointer to underlying `Vna` instance.
   */
  PreserveDataFormat(Vna *vna);


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


}       // namespace rohdeschwarz::instruments::vna
#endif  // ROHDESCHWARZ_INSTRUMENTS_VNA_PRESERVE_DATA_FORMAT_HPP
