// ======================================================================
// \title  ESP32Controller.hpp
// \author nelson
// \brief  hpp file for ESP32Controller component implementation class
// ======================================================================

#ifndef ESP32Controller_HPP
#define ESP32Controller_HPP

#include "Ref/ESP32Controller/ESP32ControllerComponentAc.hpp"

namespace Payload {

  class ESP32Controller :
    public ESP32ControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ESP32Controller
      //!
      ESP32Controller(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ESP32Controller
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ESP32Controller
      //!
      ~ESP32Controller();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for ExperimentState command handler
      //! Command to start the ESP32
      void ExperimentState_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Payload::ExperimentState experimentState 
      );


    };

} // end namespace Payload

#endif
