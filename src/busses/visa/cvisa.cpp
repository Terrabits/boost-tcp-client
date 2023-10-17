/**
* \file cvisa.cpp
* \brief rohdeschwarz::busses::visa::CVisa implementation
 */


#include "rohdeschwarz/busses/visa/cvisa.hpp"
using namespace rohdeschwarz::busses::visa;


// constants
const wchar_t* FILENAME = L"visa64.dll";


CVisa::CVisa()
  : viOpenDefaultRM(nullptr),
    viFindRsrc(nullptr),
    viFindNext(nullptr),
    viParseRsrcEx(nullptr),
    viOpen(nullptr),
    viClose(nullptr),
    viWrite(nullptr),
    viRead(nullptr),
    viEnableEvent(nullptr),
    viDisableEvent(nullptr),
    viWaitOnEvent(nullptr),
    viDiscardEvents(nullptr),
    viReadSTB(nullptr),
    viGpibSendIFC(nullptr),
    viSetAttribute(nullptr),
    viGetAttribute(nullptr),
    viStatusDesc(nullptr)
{
  // TODO: throw exception on error
  load();
}


CVisa::~CVisa()
{
  if (isVisa())
  {
    unload();
  }
}


// helpers

bool CVisa::isVisa() const
{
  return _visa.is_loaded();
}


bool CVisa::load()
{
  if (isVisa())
  {
    unload();
  }

  // load visa
  _visa = boost::dll::shared_library(FILENAME);

  if (!isVisa())
  {
    return false;
  }

  // load functions
  viOpenDefaultRM = _visa.get<VI_OPEN_DEFAULT_RM_PTR>("viOpenDefaultRM");
  viFindRsrc      = _visa.get<VI_FIND_RSRC_PTR>      ("viFindRsrc");
  viFindNext      = _visa.get<VI_FIND_NEXT_PTR>      ("viFindNext");
  viParseRsrcEx   = _visa.get<VI_PARSE_RSRC_EX_PTR>  ("viParseRsrcEx");
  viOpen          = _visa.get<VI_OPEN_PTR>           ("viOpen");
  viClose         = _visa.get<VI_CLOSE_PTR>          ("viClose");
  viWrite         = _visa.get<VI_WRITE_PTR>          ("viWrite");
  viRead          = _visa.get<VI_READ_PTR>           ("viRead");
  viEnableEvent   = _visa.get<VI_ENABLE_EVENT_PTR>   ("viEnableEvent");
  viDisableEvent  = _visa.get<VI_DISABLE_EVENT_PTR>  ("viDisableEvent");
  viWaitOnEvent   = _visa.get<VI_WAITON_EVENT_PTR>   ("viWaitOnEvent");
  viDiscardEvents = _visa.get<VI_DISCARD_EVENTS_PTR> ("viDiscardEvents");
  viReadSTB       = _visa.get<VI_READ_STB_PTR>       ("viReadSTB");
  viGpibSendIFC   = _visa.get<VI_GPIB_SEND_IFC_PTR>  ("viGpibSendIFC");
  viSetAttribute  = _visa.get<VI_SET_ATTRIBUTE_PTR>  ("viSetAttribute");
  viGetAttribute  = _visa.get<VI_GET_ATTRIBUTE_PTR>  ("viGetAttribute");
  viStatusDesc    = _visa.get<VI_STATUS_DESC_PTR>    ("viStatusDesc");

  // functions found?
  if (
      !viOpenDefaultRM
   || !viFindRsrc
   || !viFindNext
   || !viParseRsrcEx
   || !viOpen
   || !viClose
   || !viWrite
   || !viRead
   || !viEnableEvent
   || !viDisableEvent
   || !viWaitOnEvent
   || !viDiscardEvents
   || !viReadSTB
   || !viGpibSendIFC
   || !viSetAttribute
   || !viGetAttribute
   || !viStatusDesc
 )
  {
    // could not load functions
    // from library
    return false;
  }

  // success
  return true;
}


bool CVisa::unload()
{
  if (isVisa())
  {
    _visa.unload();
  }

  return !isVisa();
}
