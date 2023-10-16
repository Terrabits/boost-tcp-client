/**
* \file cvisa.hpp
* \brief rohdeschwarz::busses::visa::CVisa definition
 */


#ifndef ROHDESCHWARZ_BUSSES_VISA_CVISA_HPP
#define ROHDESCHWARZ_BUSSES_VISA_CVISA_HPP


// rohdeschwarz
#include "rohdeschwarz/busses/visa/cvisatypes.hpp"


// ivi
#include "rs-visa/visa.h"


// ms win32 api
#include <windows.h>


namespace rohdeschwarz::busses::visa
{


/**
 * \brief Runtime interface for the installed VISA C shared library
 *
 * `CVisa` attemps to load the VISA C shared library *at runtime*,
 * in the constructor. After construction, `isVisa()` should be checked to confirm that
 * VISA was successfully loaded.
 *
 * After VISA is loaded, VISA functions are exposed as function pointer
 * properties of this class.
 *
 * `CVisa` assumes familiarity with the VISA C shared library.
 */
class CVisa
{

public:


  // life cycle

  /**
   * \brief Constructor
   *
   * Attempts to load VISA. See `isVisa()` for load status.
   */
  CVisa();


  /**
   * \brief Destructor
   *
   * VISA is unloaded if it was previously loaded
   */
  ~CVisa();


  /**
   * \brief Checks if VISA was loaded
   *
   * \returns `true` if VISA C shared library was loaded; `false` otherwise
   */
  bool isVisa() const;


  // visa c functions

  /**
   * \brief Function pointer to VISA function `viOpenDefaultRM()`
   */
  VI_OPEN_DEFAULT_RM_PTR viOpenDefaultRM;


  /**
   * \brief Function pointer to VISA function `viFindRsrc`
   */
  VI_FIND_RSRC_PTR viFindRsrc;


  /**
   * \brief Function pointer to VISA function `viFindNext`
   */
  VI_FIND_NEXT_PTR viFindNext;


  /**
   * \brief Function pointer to VISA function `viParseRsrcEx`
   */
  VI_PARSE_RSRC_EX_PTR viParseRsrcEx;


  /**
   * \brief Function pointer to VISA function `viOpen`
   */
  VI_OPEN_PTR viOpen;


  /**
   * \brief Function pointer to VISA function `viClose`
   */
  VI_CLOSE_PTR viClose;


  /**
   * \brief Function pointer to VISA function `viWrite`
   */
  VI_WRITE_PTR viWrite;


  /**
   * \brief Function pointer to VISA function `viRead`
   */
  VI_READ_PTR viRead;


  /**
   * \brief Function pointer to VISA function `viEnableEvent`
   */
  VI_ENABLE_EVENT_PTR viEnableEvent;


  /**
   * \brief Function pointer to VISA function `viDisableEvent`
   */
  VI_DISABLE_EVENT_PTR viDisableEvent;


  /**
   * \brief Function pointer to VISA function `viWaitOnEvent`
   */
  VI_WAITON_EVENT_PTR viWaitOnEvent;


  /**
   * \brief Function pointer to VISA function `viDiscardEvents`
   */
  VI_DISCARD_EVENTS_PTR viDiscardEvents;


  /**
   * \brief Function pointer to VISA function `viReadSTB`
   */
  VI_READ_STB_PTR viReadSTB;


  /**
   * \brief Function pointer to VISA function `viGpibSendIFC`
   */
  VI_GPIB_SEND_IFC_PTR viGpibSendIFC;


  /**
   * \brief Function pointer to VISA function `viSetAttribute`
   */
  VI_SET_ATTRIBUTE_PTR viSetAttribute;


  /**
   * \brief Function pointer to VISA function `viGetAttribute`
   */
  VI_GET_ATTRIBUTE_PTR viGetAttribute;


  /**
   * \brief Function pointer to VISA function `viStatusDesc`
   */
  VI_STATUS_DESC_PTR viStatusDesc;


private:

  HMODULE _visa;


  // helpers

  /**
   * \brief Load VISA C shared library
   */
  bool load();


  /**
   * \brief Unload VISA C shared library
   */
  bool unload();


};  // CVisa


}       // rohdeschwarz::busses::visa
#endif  // ROHDESCHWARZ_BUSSES_VISA_CVISA_HPP
