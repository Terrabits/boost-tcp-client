/**
 * \file instrument.hpp
 * \brief rohdeschwarz::instruments::Instrument definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_INSTRUMENT_HPP
#define ROHDESCHWARZ_INSTRUMENTS_INSTRUMENT_HPP


// rohdeschwarz
#include "rohdeschwarz/scpi/block_data.hpp"
#include "rohdeschwarz/busses/visa/cvisa.hpp"
using CVisa = rohdeschwarz::busses::visa::CVisa;


// rs visa
#include "rs-visa/visatype.h"


// std lib
#include <string>
#include <vector>


namespace rohdeschwarz::instruments
{


/**
 * \brief Object-oriented R&S Instrument control
 *
 * `rohdeschwarz::instruments::Instrument` is a class for controlling any general purpose
 * instrument with VISA and SCPI. It manages the VISA
 * connection to the instrument. It also contains methods that wrap common SCPI
 * commands that apply to all general purpose instruments.
 *
 * Here is an example which demonstrates basic use:
 *
 * \include examples/instrument.cpp
 */

class Instrument
{

public:

  /**
   * \brief Constructor
   *
   * The constructor attempts to load the VISA shared library.
   */
  Instrument();

  /**
   * \brief Destructor
   *
   * If necessary, the destructor will close the VISA connection and/or unload
   * the VISA shared library.
   */
  ~Instrument();


  /**
   * \brief Check if the VISA shared library loaded
   */
  bool isVisa() const;


  // connect / disconnect

  /**
   * \brief Check for an open VISA connection to instrument
   */
  bool isOpen() const;


  /**
   * \brief Open VISA connection to instrument
   *
   * \param[in] resource   VISA resource string as a `C` style string
   * \param[in] timeout_ms VISA open timeout time, in milliseconds
   * \returns `true` on success; `false` otherwise
   */
  bool open(const char* resource, unsigned int timeout_ms = 2000);


  /**
   * \brief Open VISA connection to instrument
   *
   * \param[in] resource   VISA resource string as a `C++` style string
   * \param[in] timeout_ms open timeout time, in milliseconds
   * \returns `true` on success; `false` otherwise
   */
  bool open(const std::string& resource, unsigned int timeout_ms = 2000);


  /**
   * \brief Close VISA connection to instrument
   */
  bool close();


  // timeout

  /**
   * \brief Query VISA timeout, in milliseconds
   */
  int timeout_ms();


  /**
   * \brief Set VISA timeout
   *
   * \param[in] timeout_ms VISA timeout, in milliseconds
   */
  bool setTimeout(int timeout_ms);


  // binary io

  /**
   * \brief Writes binary data to instrument
   *
   * \param[in] data binary data to be written
   */
  void binaryWrite(const std::vector<unsigned char> &data);


  /**
   * \brief Reads binary data from instrument
   *
   * \param[in] bufferSize_B size of the read buffer, in bytes
   * \returns binary data read from instrument
   */
  std::vector<unsigned char> binaryRead(unsigned int bufferSize_B = 1024);


  /**
   * \brief Perform binary query
   *
   * \param[in] data binary data to be written to instrument
   * \param[in] bufferSize_B buffer size for binary read, in bytes
   * \returns binary data read from instrument
   */
  std::vector<unsigned char> binaryQuery(std::vector<unsigned char> data, unsigned int bufferSize_B = 1024);


  // block data io

  /**
   * \brief Read Block Data
   *
   * `readBlockData` reads data in IEEE 488.2 Block Data format.
   */
  scpi::BlockData readBlockData(unsigned int bufferSize_B = 1024);


  /**
   * \brief Queries Block Data
   *
   * `queryBlockData` reads data in IEEE 488.2 Block Data format.
   *
   * \param[in] scpi query SCPI command
   * \param[in] bufferSize_B buffer size for reading Block Data, in bytes
   * \returns Block Data read
   */
  scpi::BlockData queryBlockData(const std::string &scpi, unsigned int bufferSize_B = 1024);


  // string io

  /**
   * \brief Writes C++ style SCPI string to instrument
   */
  void write(const std::string &scpi);


  /**
   * \brief Reads C++ style string from instrument
   */
  std::string read(unsigned int bufferSize_B = 1024);


  /**
   * \brief Performs SCPI query with C++ style strings
   */
  std::string query(const std::string &scpi, unsigned int bufferSize_B = 1024);


  // status

  /**
   * \brief Checks VISA status for an error
   */
  bool isError() const;


  /**
   * \brief Gets VISA status
   */
  ViStatus status() const;


  /**
   * \brief Gets VISA status as a human-readable message
   */
  std::string statusMessage();


  // common scpi

  /**
   * \brief Queries instrument ID string
   *
   * `id` uses SCPI query `*IDN?`
   */
  std::string id();       // *IDN?


  /**
   * \brief Queries instrument options string
   *
   * `options` uses SCPI query `*OPT?`
   */
  std::string options();  // *OPT?


  /**
   * \brief Clears SCPI errors
   *
   * `clearErrors` sends SCPI command `*CLS`
   */
  void clearErrors();    // *CLS


  /**
   * \brief Perform instrument preset
   *
   * `reset` sends SCPI command `*RST`
   */
  void reset();           // *RST


  /**
   * \brief Instructs instrument to perform previous SCPI commands before proceeding
   *
   * `wait` sends SCPI command `*WAI`
   */
  void wait();            // *WAI


  /**
   * \brief Queries operation complete in a non-blocking way
   *
   * `isOperationComplete` queries SCPI command `*OPC`
   */
  bool isOperationComplete();  // *OPC


  /**
   * \brief Does not return until operations are complete or timeout occurs
   *
   * `blockUntilOperationComplete` queries SCPI command `*OPC?`
   */
  bool blockUntilOperationComplete(unsigned int timeout_ms = 2000);  // *OPC?


private:
  CVisa     _visa;
  ViSession _resource_manager;
  ViSession _instrument;
  ViStatus  _status;


  // helpers

  /**
   * \brief Opens default VISA resource manager
   *
   * \returns true if successful; false otherwise
   */
  bool openDefaultRM();


  /**
   * \brief Reads VISA attribute
   */
  ViAttrState attribute(ViAttr attribute);


  /**
   * \brief Sets VISA attribute
   */
  bool setAttribute(ViAttr attribute, ViAttrState value);


  /**
   * \brief Converts C++ style string to binary data
   */
  static std::vector<unsigned char> binaryCopy(const std::string &input);


};  // Instrument


}       // rohdeschwarz::instruments
#endif  // ROHDESCHWARZ_INSTRUMENTS_INSTRUMENT_HPP
