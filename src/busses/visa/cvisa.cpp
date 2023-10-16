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
    viStatusDesc(nullptr),
    _visa(nullptr)
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
  return _visa != nullptr;
}


bool CVisa::load()
{
  if (isVisa())
  {
    unload();
  }

  // load visa
  _visa = LoadLibrary(FILENAME);
  if (!isVisa())
  {
    return false;
  }

  // load functions
  viOpenDefaultRM = reinterpret_cast<VI_OPEN_DEFAULT_RM_PTR>(GetProcAddress(_visa, "viOpenDefaultRM"));
  viFindRsrc = reinterpret_cast<VI_FIND_RSRC_PTR>(GetProcAddress(_visa, "viFindRsrc"));
  viFindNext = reinterpret_cast<VI_FIND_NEXT_PTR>(GetProcAddress(_visa, "viFindNext"));
  viParseRsrcEx = reinterpret_cast<VI_PARSE_RSRC_EX_PTR>(GetProcAddress(_visa, "viParseRsrcEx"));
  viOpen = reinterpret_cast<VI_OPEN_PTR>(GetProcAddress(_visa, "viOpen"));
  viClose = reinterpret_cast<VI_CLOSE_PTR>(GetProcAddress(_visa, "viClose"));
  viWrite = reinterpret_cast<VI_WRITE_PTR>(GetProcAddress(_visa, "viWrite"));
  viRead = reinterpret_cast<VI_READ_PTR>(GetProcAddress(_visa, "viRead"));
  viEnableEvent = reinterpret_cast<VI_ENABLE_EVENT_PTR>(GetProcAddress(_visa, "viEnableEvent"));
  viDisableEvent = reinterpret_cast<VI_DISABLE_EVENT_PTR>(GetProcAddress(_visa, "viDisableEvent"));
  viWaitOnEvent = reinterpret_cast<VI_WAITON_EVENT_PTR>(GetProcAddress(_visa, "viWaitOnEvent"));
  viDiscardEvents = reinterpret_cast<VI_DISCARD_EVENTS_PTR>(GetProcAddress(_visa, "viDiscardEvents"));
  viReadSTB = reinterpret_cast<VI_READ_STB_PTR>(GetProcAddress(_visa, "viReadSTB"));
  viGpibSendIFC = reinterpret_cast<VI_GPIB_SEND_IFC_PTR>(GetProcAddress(_visa, "viGpibSendIFC"));
  viSetAttribute = reinterpret_cast<VI_SET_ATTRIBUTE_PTR>(GetProcAddress(_visa, "viSetAttribute"));
  viGetAttribute = reinterpret_cast<VI_GET_ATTRIBUTE_PTR>(GetProcAddress(_visa, "viGetAttribute"));
  viStatusDesc = reinterpret_cast<VI_STATUS_DESC_PTR>(GetProcAddress(_visa, "viStatusDesc"));

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
  if (!isVisa())
  {
    // not loaded
    return true;
  }

  // unload
  return FreeLibrary(_visa);
}
