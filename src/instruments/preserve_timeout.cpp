/**
 * \file preserve_timeout.cpp
 * \brief rohdeschwarz::instruments::PreserveTimeout implementation
 */


#include "rohdeschwarz/instruments/preserve_timeout.hpp"
using namespace rohdeschwarz::instruments;


PreserveTimeout::PreserveTimeout(Instrument *instrument) :
  _timeout_ms(instrument->timeout_ms()),
  _instrument(instrument)
{
  // TODO: throw exception on visa error?
}


PreserveTimeout::~PreserveTimeout()
{
  _instrument->setTimeout(_timeout_ms);
  // TODO: throw exception on visa error?
}
