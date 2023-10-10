/**
 * \file preserve_timeout.cpp
 * \brief RsVisa::PreserveTimeout implementation
 */


#include "preserve_timeout.hpp"
using namespace RsVisa;


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
