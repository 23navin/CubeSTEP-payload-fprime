// ======================================================================
// \title  ESP32Controller.cpp
// \author kana
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
    this->log_ACTIVITY_HI_ExperimentStatus(experimentState);
    this->
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  // ----------------------------------------------------------------------
  // Helper Functions
  // ----------------------------------------------------------------------

  Drv::I2cStatus ESP32Controller ::setupReadRegister(U8 reg) {
    Fw::Buffer buffer(&reg, sizeof reg);
    return this->write_out(0, m_i2cDevAddress, buffer);
  }

  Drv::I2cStatus ESP32Controller ::readRegisterBlock(U8 startRegister, Fw::Buffer& buffer) {
    Drv::I2cStatus status;
    status = this->setupReadRegister(startRegister);
    if(status == Drv::I2cStatus::I2C_OK) {
      status = this->read_out(0, m_i2cDevAddress, buffer);
    }
    return status;
  }

  void ESP32Controller ::config() {

  }

  void ESP32Controller ::power() {
    
  }

} // end namespace Payload
