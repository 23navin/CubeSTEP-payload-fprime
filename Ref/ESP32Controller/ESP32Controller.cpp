// ======================================================================
// \title  ESP32Controller.cpp
// \author nelson
// \brief  cpp file for ESP32Controller component implementation class
// ======================================================================


#include <Ref/ESP32Controller/ESP32Controller.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Payload {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ESP32Controller ::
    ESP32Controller(
        const char *const compName
    ) : ESP32ControllerComponentBase(compName)
  {

  }

  void ESP32Controller ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ESP32ControllerComponentBase::init(queueDepth, instance);
  }

  ESP32Controller ::
    ~ESP32Controller()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void ESP32Controller ::
    ExperimentState_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Payload::ExperimentState experimentState
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Payload
