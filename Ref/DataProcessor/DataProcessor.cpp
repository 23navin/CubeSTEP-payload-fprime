// ======================================================================
// \title  DataProcessor.cpp
// \author nelson
// \brief  cpp file for DataProcessor component implementation class
// ======================================================================


#include <Ref/DataProcessor/DataProcessor.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Payload {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  DataProcessor ::
    DataProcessor(
        const char *const compName
    ) : DataProcessorComponentBase(compName)
  {

  }

  void DataProcessor ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    DataProcessorComponentBase::init(queueDepth, instance);
  }

  DataProcessor ::
    ~DataProcessor()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void DataProcessor ::
    preProcess_handler(
        const NATIVE_INT_TYPE portNum,
        Payload::TemperatureData &tempData
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void DataProcessor ::
    SetTemperatureScale_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Payload::TemperatureScale temperatureScale
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Payload
