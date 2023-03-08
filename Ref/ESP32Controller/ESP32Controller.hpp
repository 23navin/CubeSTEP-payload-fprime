// ======================================================================
// \title  ESP32Controller.hpp
// \author kana
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
    void config();

    //! Turn experiment on or off
    //!
    void experiment(PowerState powerState);

    //! Read, telemeter, and update local copy of Payload data
    //!
    void update();

    // ----------------------------------------------------------------------
    // Member Variables
    // ----------------------------------------------------------------------
    I2cDevAddr::T m_i2cDevAddress; //!< Stored device address
    };

} // end namespace Payload

#endif
