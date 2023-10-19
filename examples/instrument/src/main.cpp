/**
 * \file instrument.cpp
 * \brief RsVisa::Instrument example
 *
 * This example demonstrates basic use of `RsVisa::Instrument`.
 *
 * \include instrument.cpp
 */

// RsVisa
#include "RsVisa/instrument.hpp"


// std lib
#include <cassert>
#include <iostream>


void main()
{
  // create an Instrument object
  // constructor loads VISA shared library
  auto instr = RsVisa::Instrument();

  // is VISA loaded?
  assert(instr.isVisa());

  // connect to instrument
  instr.open("TCPIP::localhost::INSTR");

  // is instrument connected?
  assert(instr.isOpen());

  // query instrument id
  std::cout << "id: " << instr.id() << std::endl;
}
