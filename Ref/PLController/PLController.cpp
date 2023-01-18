// ======================================================================
// \title  PLController.cpp
// \author nelson
// \brief  cpp file for PLController component implementation class
// ======================================================================


#include <Ref/PLController/PLController.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Payload {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PLController ::
    PLController(
        const char *const compName
    ) : PLControllerComponentBase(compName)
  {

  }

  void PLController ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    PLControllerComponentBase::init(queueDepth, instance);
  }

  PLController ::
    ~PLController()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void PLController ::
    TemperatureData_handler(
        const NATIVE_INT_TYPE portNum,
        Payload::TemperatureData &tempData
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void PLController ::
    ExpStart_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Payload::ExpParams expParams
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void PLController ::
    ExpStop_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        bool stopType
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void PLController ::
    ExpConfig_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Payload::ExpParams expParams
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void PLController ::
    PLStatus_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void PLController ::
    ExpResults_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Payload
