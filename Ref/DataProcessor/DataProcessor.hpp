// ======================================================================
// \title  DataProcessor.hpp
// \author nelson
// \brief  hpp file for DataProcessor component implementation class
// ======================================================================

#ifndef DataProcessor_HPP
#define DataProcessor_HPP

#include "Ref/DataProcessor/DataProcessorComponentAc.hpp"

namespace Payload {

  class DataProcessor :
    public DataProcessorComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object DataProcessor
      //!
      DataProcessor(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object DataProcessor
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object DataProcessor
      //!
      ~DataProcessor();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for preProcess
      //!
      void preProcess_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Payload::TemperatureData &tempData /*!< 
      Port that carries raw temp data
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SetTemperatureScale command handler
      //! Set the format to convert to from raw image file
      void SetTemperatureScale_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Payload::TemperatureScale temperatureScale /*!< 
          Type of file format to convert to
          */
      );


    };

} // end namespace Payload

#endif
