// ======================================================================
// \title  PLController.hpp
// \author nelson
// \brief  hpp file for PLController component implementation class
// ======================================================================

#ifndef PLController_HPP
#define PLController_HPP

#include "Ref/PLController/PLControllerComponentAc.hpp"

namespace Payload {

  class PLController :
    public PLControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PLController
      //!
      PLController(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object PLController
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object PLController
      //!
      ~PLController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for TemperatureData
      //!
      void TemperatureData_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Payload::TemperatureData &tempData /*!< 
      Port that carries raw temp data
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for ExpStart command handler
      //! Command to tell ESP32 to begin experiment
      void ExpStart_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Payload::ExpParams expParams /*!< 
          Experiment parameters
          */
      );

      //! Implementation for ExpStop command handler
      //! Command to tell ESP32 to halt experiment
      void ExpStop_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          bool stopType /*!< 
          should the experiment stop immediately or after current increment test
          */
      );

      //! Implementation for ExpConfig command handler
      //! Command to configure the experiment parameters
      void ExpConfig_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Payload::ExpParams expParams /*!< 
          Experiment parameters
          */
      );

      //! Implementation for PLStatus command handler
      //! Command to request a payload status update from the ESP32
      void PLStatus_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for ExpResults command handler
      //! Command to request the experiment results
      void ExpResults_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace Payload

#endif
