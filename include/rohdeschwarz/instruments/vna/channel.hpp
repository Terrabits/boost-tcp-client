/**
* \file channel.hpp
* \brief rohdeschwarz::instruments::vna::Channel definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_VNA_CHANNEL_HPP
#define ROHDESCHWARZ_INSTRUMENTS_VNA_CHANNEL_HPP


// std lib
#include <vector>


namespace rohdeschwarz::instruments::vna
{


// forward declarations
class Vna;


/** \brief Object-oriented measurement channel control
 *
 * `Channel` provides object-oriented control of an R&S ZNX-series VNA Channel
 * via a VISA connection and SCPI commands.
 */
class Channel
{

public:


  /**
   * \brief Constructor
   *
   * \param[in] vna   pointer to underlying `Vna` instance
   * \param[in] index channel index
   */
  Channel(Vna *vna, unsigned int index);


  /**
   * \brief channel index
   */
  unsigned int index() const;


  // points

  /**
   * \brief queries the number of measurement points
   */
  unsigned int points();


  /**
   * \brief sets number of measurement points
   *
   * \param[in] points number of measurement points
   */
  void setPoints(unsigned int points);


  // start frequency (Hz)

  /**
   * \brief queries the start frequency of measurement, in `Hz`
   */
  double startFrequency_Hz();


  /**
   * \brief sets the start frequency of the measurement
   *
   * \param[in] frequency_Hz the start frequency of the measurement, in `Hz`
   */
  void setStartFrequency(double frequency_Hz);


  // stop frequency (Hz)

  /**
   * \brief queries the stop frequency of the measurement, in `Hz`
   */
  double stopFrequency_Hz();


  /**
   * \brief sets the stop frequency of the measurement
   *
   * \param[in] frequency_Hz the stop frequency of the measurement, in `Hz`
   */
  void setStopFrequency(double frequency_Hz);


  /**
   * \brief queries the measurement frequencies, in `Hz`
   */
  std::vector<double> frequencies_Hz();


private:

  Vna*         _vna;
  unsigned int _index;


};  // Channel


}       // rohdeschwarz::instruments::vna
#endif  // ROHDESCHWARZ_INSTRUMENTS_VNA_CHANNEL_HPP
