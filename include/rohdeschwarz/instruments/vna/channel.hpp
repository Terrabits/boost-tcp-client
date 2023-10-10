/**
* \file channel.hpp
* \brief RsVisa::Channel definition
 */


#ifndef RS_VISA_CHANNEL_HPP
#define RS_VISA_CHANNEL_HPP


// std lib
#include <vector>


namespace RsVisa
{


// forward declarations
class Znx;


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
   * \param[in] znx   pointer to underlying `Znx` instance
   * \param[in] index channel index
   */
  Channel(Znx *znx, unsigned int index);


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

  Znx*         _znx;
  unsigned int _index;


};


}       // RsVisa
#endif  // RS_VISA_CHANNEL_HPP
