module Payload {

enum TemperatureScale {Fahrenheit = 0, Celsius = 1}

  @ Component for processing raw temperature data
  active component DataProcessor {
    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Save temperature data to logger
    output port postProcess: Fw.BufferSend  @< postProcess -> send temperature data to buffer

    @ Image data to be processed
    async input port preProcess: tempData @< preProcess -> find temperature data

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Port for emitting events
    event port Log

    @ Port for emitting text events
    text event port LogText

    @ Port for getting the time
    time get port Time

    @ Telemetry port
    telemetry port Tlm

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Set the format to convert to from raw image file
    async command SetTemperatureScale(
        temperatureScale: TemperatureScale @< Type of file format to convert to
        ) \
    opcode 0x01

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Event bad buffer size
    event BadBufferSize(
        encodeSize: U32 @< Size of allocated buffer to store output buffer from imencode
        bufferSize: U32 @< Size of output buffer from imencode
    ) \
    severity warning high \
    format "Encode buffer of size {} is smaller than buffer of size {}"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ Total number of experiments completed
    telemetry dataProcessed: U32 id 0 update on change

  }

}

