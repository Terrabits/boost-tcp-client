/**
* \file preserve_timeout.hpp
* \brief rohdeschwarz::instruments::PreserveTimeout definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_PRESERVE_TIMEOUT_HPP
#define ROHDESCHWARZ_INSTRUMENTS_PRESERVE_TIMEOUT_HPP


// rohdeschwarz
#include "rohdeschwarz/instruments/instrument.hpp"


namespace rohdeschwarz::instruments
{

/**
 * \brief Class for preserving the VISA timeout value in a particular scope.
 *
 * `PreserveTimeout` is intended for use in methods that require a
 * particular timeout value, but want to preserve the
 * timeout value set by the user.
 *
 * On construction, `PreserveTimeout` stores the current timeout value.
 * On destruction, the timeout value is restored.
 */
class PreserveTimeout
{

public:

  // life cycle

  /**
   * \brief Constructor
   *
   * Stores the current timeout value
   *
   * \param[in] instrument Pointer to underlying `Instrument` instance.
   */
  PreserveTimeout(Instrument *instrument);


  /**
   * \brief Destructor
   *
   * Restores the timeout value stored during construction.
   */
  ~PreserveTimeout();

private:

  unsigned int _timeout_ms;
  Instrument*  _instrument;


};  // PreserveTimeout


}       // rohdeschwarz::instruments
#endif  // ROHDESCHWARZ_INSTRUMENTS_PRESERVE_TIMEOUT_HPP
