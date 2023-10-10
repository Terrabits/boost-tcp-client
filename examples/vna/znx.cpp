/**
 * \file znx.cpp
 * \brief RsVisa::Znx example
 *
 * This example demonstrates basic use of `RsVisa::Znx`.
 *
 * \include znx.cpp
 */

// RsVisa
#include "RsVisa/znx.hpp"


// std lib
#include <cassert>
#include <iostream>


void main()
{
  // create a Znx object
  // constructor loads VISA shared library
  auto znx = RsVisa::Znx();

  // is VISA loaded?
  assert(znx.isVisa());

  // connect to znx
  znx.open("TCPIP::localhost::znx");

  // is znx connected?
  assert(znx.isOpen());

  // start from instrument preset:
  // - Channels: 1
  // - Traces:   Trc1
  // - Diagrams: 1
  znx.reset();

  // configure channel 1:
  // sweep from 1 GHz to 2 GHz with 201 points
  auto ch1 = znx.channel(1);
  ch1.setStartFrequency(1e9);
  ch1.setStopFrequency(2e9);
  ch1.setPoints(201);

  // create trace Trc2
  znx.createTrace("Trc2");

  // configure trace for |S11| in dB
  auto trc2 = znx.trace("Trc2");
  trc2.setParameter("S11");
  trc2.setFormat("MLOG");

  // display Trc2 in diagram
  trc2.setDiagram(1);
}
