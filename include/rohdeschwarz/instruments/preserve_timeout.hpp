/**
* \file preserve_timeout.hpp
* \brief RsVisa::PreserveTimeout definition
 */


#ifndef RS_VISA_PRESERVE_TIMEOUT_HPP
#define RS_VISA_PRESERVE_TIMEOUT_HPP


// RsVisa
#include "instrument.hpp"


namespace RsVisa
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


};  // class PreserveTimeout


}  // namespace RsVisa
#endif  // RS_VISA_PRESERVE_TIMEOUT_HPP
