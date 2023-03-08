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
      // Constants and Types
      // ----------------------------------------------------------------------

      //! The I2C device addresses
      struct I2cDevAddr {
        enum T {
          //! The I2C device address with AD0 set to zero
          AD0_0 = 0x68,
          //! The I2C device address with AD0 set to one
          AD0_1 = 0x69
        };
      };

      //TODO -- add registeres 

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

    // ----------------------------------------------------------------------
    // Helper Functions
    // ----------------------------------------------------------------------

    /**
     * \brief sets up the ESP32 to know what register the next read should be from
     *
     * The Payload Processer requires a write call with a register's address before a read will function correctly. This helper
     * sets up that read address by writing it to the ESP32 via the I2C write port.
     *
     * \param reg: ESP32 internal address to the first register to be read
     * \return: I2C from the write call
     */
    Drv::I2cStatus setupReadRegister(U8 reg);

    /**
     * \brief reads a block of registers from the IMU
     *
     * This function starts by writing the startRegister to the ESP32 by passing it to `setupReadRegister`. It then calls
     * the read port of the I2C bus to read data from the ESP32. It will read `buffer.getSize()` bytes from the I2C device
     * and as such the caller must set this up.
     *
     * \param startRegister: register address to start reading from
     * \param buffer: buffer to read into. Determines size of read.
     * \return: I2C status of transactions
     */
    Drv::I2cStatus readRegisterBlock(U8 startRegister, Fw::Buffer& buffer);

    //! Configure the PayloadProcessor
    //!
    void config(ExpParams expParams);

    //! Turn experiment on or off
    //!
    void experimentStart();

    void experimentStop();

    void forceStop();

    //! Read, telemeter, and update local copy of Payload status
    //!
    void updateStatus();

    //! Receive experiment data
    //!
    void experimentData();

    // ----------------------------------------------------------------------
    // Member Variables
    // ----------------------------------------------------------------------
    I2cDevAddr::T m_i2cDevAddress; //!< Stored device address
    };

} // end namespace Payload

#endif
