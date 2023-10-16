#ifndef ROHDESCHWARZ_BUSSES_VISA_VISA_HPP
#define ROHDESCHWARZ_BUSSES_VISA_VISA_HPP


// rohdeschwarz
#include "rohdeschwarz/busses/bus.hpp"
#include "rohdeschwarz/busses/visa/cvisa.hpp"


namespace rohdeschwarz::busses::visa
{


class Visa : public rohdeschwarz::busses::Bus
{


public:

  // TODO


private:

  CVisa _visa;


};  // class Bus


}       // rohdeschwarz::busses::visa
#endif  // ROHDESCHWARZ_BUSSES_VISA_VISA_HPP
