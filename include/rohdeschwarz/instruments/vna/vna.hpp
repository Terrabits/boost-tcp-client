/**
 * \file vna.hpp
 * \brief rohdeschwarz::instruments::vna::Vna definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_VNA_VNA_HPP
#define ROHDESCHWARZ_INSTRUMENTS_VNA_VNA_HPP


// rohdeschwarz
#include "rohdeschwarz/instruments/instrument.hpp"
#include "rohdeschwarz/instruments/vna/channel.hpp"
#include "rohdeschwarz/instruments/vna/data_format.hpp"
#include "rohdeschwarz/instruments/vna/display.hpp"
#include "rohdeschwarz/instruments/vna/trace.hpp"


// std lib
#include <string>
#include <vector>


namespace rohdeschwarz::instruments::vna
{

/** \brief Object-oriented R&S ZNX-series VNA control
 *
 * `Vna` provides object-oriented control of a Rohde & Schwarz
 * ZNX-series Vector Network Analyzer via a VISA connection
 * and SCPI commands.
 */
class Vna : public rohdeschwarz::instruments::Instrument
{

public:

  /**
   * \brief Object-oriented control of the display
   */
  Display display();


  /**
   * \brief Object-oriented control of the data transfer format
   */
  DataFormat dataFormat();


  // channels


  /**
   * \brief Checks for existence of channel `index`
   *
   * \param[in] index channel index
   */
  bool isChannel(unsigned int index);


  /**
   * \brief Create new channel with specified index
   *
   * \param[in] index channel index
   */
  Channel createChannel(unsigned int index);


  /**
   * \brief Object-oriented control of a measurement channel
   *
   * \param[in] index channel index
   */
  Channel channel(unsigned int index);


  /**
   * \brief Query existing channels, by indexes
   */
  std::vector<unsigned int> channels();


  // traces


  /**
   * \brief Checks for existence of a trace by name
   *
   * \param[in] name trace name as a `C` style string
   */
  bool isTrace(const char* name);


  /**
   * \brief Checks for existence of a trace by name
   *
   * \param[in] name trace name as a `C++` style string
   */
  bool isTrace(const std::string &name);


  /**
   * \brief  Creates a new trace
   *
   * \param[in] name    name of the created trace as `C` style string
   * \param[in] channel channel index of created trace
   */
  Trace createTrace(const char* name, unsigned int channel = 1);


  /**
   * \brief Creates a new trace
   *
   * \param[in] name    name of the created trace as a `C++` style string
   * \param[in] channel channel index of the created trace
   */
  Trace createTrace(const std::string& name, unsigned int channel = 1);


  /**
   * \brief Object-oriented control of a trace
   *
   * \param[in] name trace name as a `C` style string
   */
  Trace trace(const char* name);


  /**
   * \brief Object-oriented control of a trace
   *
   * \param[in] name trace name as a `C++` style string
   */
  Trace trace(const std::string &name);


  /**
   * \brief Query existing traces by name
   */
  std::vector<std::string> traces();


};


}       // namespace rohdeschwarz::instruments::vna
#endif  // ROHDESCHWARZ_INSTRUMENTS_VNA_VNA_HPP
