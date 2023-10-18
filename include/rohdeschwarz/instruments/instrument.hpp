/**
 * \file instrument.hpp
 * \brief rohdeschwarz::instruments::Instrument definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_INSTRUMENT_HPP
#define ROHDESCHWARZ_INSTRUMENTS_INSTRUMENT_HPP


// rohdeschwarz
#include "rohdeschwarz/busses/bus.hpp"
#include "rohdeschwarz/scpi/block_data.hpp"
#include "rohdeschwarz/scpi/bool.hpp"
#include "rohdeschwarz/helpers.hpp"
#include "rohdeschwarz/to_value.hpp"


// rs visa
#include "rs-visa/visatype.h"


// boost
#include "boost/format.hpp"


// std lib
#include <complex>
#include <cstddef>
#include <memory>
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


  // open / close connection

  /**
   * \brief Check for an open connection to an instrument
   */
  bool isOpen() const;


  /**
   * \brief Open VISA connection to instrument
   *
   * \param[in] resource   VISA resource string as a `C++` style string
   * \param[in] timeout_ms open timeout time, in milliseconds
   * \returns `true` on success; `false` otherwise
   */
  bool openVisa(std::string resource, unsigned int timeout_ms = 2000);


  /**
   * \brief Open tcp socket connection to an instrument
   *
   * Attempts to connect to the instrument at `host` with a TCP socket on port `5025`.
   *
   * \param[in] host             host name or ip address
   * \param[in] timeout_ms open  timeout time, in milliseconds
   * \returns `true` on success; `false` otherwise
   */
  bool openTcp(std::string host, unsigned int timeout_ms = 2000);


  /**
   * \brief Close the connection to the instrument
   */
  void close();


  // io buffer

  std::size_t bufferSize_B() const;

  void setBufferSize(std::size_t size_bytes);

  std::vector<unsigned char>* buffer();

  const std::vector<unsigned char>* buffer() const;

  std::vector<unsigned char> takeData();


  // timeout

  /**
   * \brief Query IO timeout time, in milliseconds
   */
  int timeout_ms();


  /**
   * \brief Set IO timeout time
   *
   * \param[in] timeout_ms timeout, in milliseconds
   */
  bool setTimeout(int timeout_ms);


  // raw io

  bool readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize = nullptr);


  bool writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize = nullptr);


  // raw io with internal buffers

  bool readData(std::size_t* readSize = nullptr);


  // string io

  std::string read();


  template<class... Args>
  bool write(std::string scpi_command, Args&&... args)
  {
    // format scpi command
    auto format = boost::format(scpi_command);
    ([&]
    {
      format % args;
    } (), ...);

    // get complete command string
    auto command = format.str();

    // get data pointer, size
    using uchar_p = unsigned char*;
    auto data = uchar_p(command.c_str());
    auto size = command.size();

    // write data
    std::size_t writeSize;
    if (!writeData(data, size, &writeSize))
    {
      // error
      return false;
    }

    // write complete?
    return writeSize == size;
  }


  template<class... Args>
  std::string query(std::string scpi_command, Args&&... args)
  {
    // write
    if (!write(scpi_command, &args...))
    {
      // error
      return std::string();
    }

    // read
    return read();
  }


  // basic type io

  template<class OutputType>
  OutputType readValue()
  {
    return to_value<OutputType>(read());
  }


  template<class OutputType, class... Args>
  OutputType queryValue(std::string scpi_command, Args&&... args)
  {
    return to_value<OutputType>(query(scpi_command, &args...));
  }

  // scpi bool io

  bool readScpiBool();

  template<class... Args>
  bool queryScpiBool(std::string scpi_command, Args&&... args)
  {
    // write
    if (!write(scpi_command, &args...))
    {
      // error
      return false;
    }

    // parse result
    return rohdeschwarz::scpi::toBool(read());
  }


  // ascii data vector io

  /**
   * \brief reads ascii data and parses it into vector <double>
   */
  std::vector<double> readAsciiVector();


  /**
   * \brief reads ascii data and parses it into vector <complex <double>>
   */
  std::vector<std::complex<double>> readAsciiComplexVector();


  // block data io

  /**
   * \brief Read Block Data
   *
   * `readBlockData` reads data in IEEE 488.2 Block Data format.
   */
  scpi::BlockData readBlockData();


  // block data vector io

  /**
   * \brief Reads block data and parses it into vector <double>
   */
  std::vector<double> read64BitVector();


  /**
   * \brief Reads block data and parses it into vector <complex <double>>
   */
  std::vector<std::complex<double>> read64BitComplexVector();


  // status

  /**
   * \brief Checks the bus status for an error
   */
  bool isBusError() const;


  /**
   * \brief Gets the bus status as a human-readable string
   */
  std::string busStatus() const;


  // common scpi commands

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
  void preset();           // *RST


  /**
   * \brief Instructs instrument to perform previous SCPI commands before proceeding
   *
   * `wait` sends SCPI command `*WAI`
   */
  void wait();            // *WAI


  /**
   * \brief Queries *OPC? - block until operation complete
   */
  bool blockUntilOperationComplete(unsigned int timeout_ms = 2000);


private:

  std::shared_ptr<rohdeschwarz::busses::Bus> _bus;


};  // Instrument


}       // rohdeschwarz::instruments
#endif  // ROHDESCHWARZ_INSTRUMENTS_INSTRUMENT_HPP
