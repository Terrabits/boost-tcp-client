/**
 * \file cvisatypes.hpp
 * \brief VISA C function pointer types
 */


#ifndef ROHDESCHWARZ_BUSSES_VISA_CVISATYPES_HPP
#define ROHDESCHWARZ_BUSSES_VISA_CVISATYPES_HPP


// ivi foundation
#include "visa.h"


namespace rohdeschwarz::busses::visa
{


// define function pointer types

/**
 * \brief Function pointer type for `viOpenDefaultRM`
 */
typedef ViStatus(_VI_FUNC * VI_OPEN_DEFAULT_RM_PTR)(ViPSession vi);


/**
 * \brief Function pointer type for `viFindRsrc`
 */
typedef ViStatus(_VI_FUNC * VI_FIND_RSRC_PTR)(ViSession sesn, ViString expr, ViPFindList vi, ViPUInt32 retCnt, ViChar _VI_FAR desc[]);


/**
 * \brief Function pointer type for `viFindNext`
 */
typedef ViStatus(_VI_FUNC * VI_FIND_NEXT_PTR)(ViFindList vi, ViChar _VI_FAR desc[]);


/**
 * \brief Function pointer type for `viParseRsrcEx`
 */
typedef ViStatus(_VI_FUNC * VI_PARSE_RSRC_EX_PTR)(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType, ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[], ViChar _VI_FAR expandedUnaliasedName[], ViChar _VI_FAR aliasIfExists[]);


/**
 * \brief Function pointer type for `viOpen`
 */
typedef ViStatus(_VI_FUNC * VI_OPEN_PTR)(ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi);


/**
 * \brief Function pointer type for `viClose`
 */
typedef ViStatus(_VI_FUNC * VI_CLOSE_PTR)(ViObject vi);


/**
 * \brief Function pointer type for `viWrite`
 */
typedef ViStatus(_VI_FUNC * VI_WRITE_PTR)(ViSession vi, ViBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);


/**
 * \brief Function pointer type for `viRead`
 */
typedef ViStatus(_VI_FUNC * VI_READ_PTR)(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);


/**
 * \brief Function pointer type for `viEnableEvent`
 */
typedef ViStatus(_VI_FUNC * VI_ENABLE_EVENT_PTR)(ViSession vi, ViEventType eventType, ViUInt16 mechanism, ViEventFilter context);


/**
 * \brief Function pointer type for `viDisableEvent`
 */
typedef ViStatus(_VI_FUNC * VI_DISABLE_EVENT_PTR)(ViSession vi, ViEventType eventType, ViUInt16 mechanism);


/**
 * \brief Function pointer type for `viWaitOnEvent`
 */
typedef ViStatus(_VI_FUNC * VI_WAITON_EVENT_PTR)(ViSession vi, ViEventType inEventType, ViUInt32 timeout, ViPEventType outEventType, ViPEvent outContext);


/**
 * \brief Function pointer type for `viDiscardEvents`
 */
typedef ViStatus(_VI_FUNC * VI_DISCARD_EVENTS_PTR)(ViSession vi, ViEventType eventType, ViUInt16 mechanism);


/**
 * \brief Function pointer type for `viReadSTB`
 */
typedef ViStatus(_VI_FUNC * VI_READ_STB_PTR)(ViSession vi, ViPUInt16 status);


/**
 * \brief Function pointer type for `viGpibSendIFC`
 */
typedef ViStatus(_VI_FUNC * VI_GPIB_SEND_IFC_PTR)(ViSession vi);


/**
 * \brief Function pointer type for `viSetAttribute`
 */
typedef ViStatus(_VI_FUNC * VI_SET_ATTRIBUTE_PTR)(ViObject vi, ViAttr attrName, ViAttrState attrValue);


/**
 * \brief Function pointer type for `viGetAttribute`
 */
typedef ViStatus(_VI_FUNC * VI_GET_ATTRIBUTE_PTR)(ViObject vi, ViAttr attrName, void _VI_PTR attrValue);


/**
 * \brief Function pointer type for `viStatusDesc`
 */
typedef ViStatus(_VI_FUNC * VI_STATUS_DESC_PTR)(ViObject vi, ViStatus status, ViChar _VI_FAR desc[]);


}       // rohdeschwarz::busses::visa
#endif  // ROHDESCHWARZ_BUSSES_VISA_CVISATYPES_HPP
