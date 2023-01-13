module Payload {
  enum ExperimentState {Inactive, Active}

  @ Type used for telemetry for 16 temp sensors
  array TempData = [16] U32

  @ Component to control experiment processor and collect temperature data
  active component ESP32Controller {
    # General Ports
    @ Sends temperature data to another component to be processed
    output port process: tempData

    @ Port that reads data from ESP32
    output port read: Drv.I2c

    @ Port that writes data to ESP32
    output port write: Drv.I2c

    # Special Ports
    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ command response
    command resp port cmdResponseOut

    @ Port for emitting events
    event port Log

    @ Port for emitting text events
    text event port LogText

    @ Port for getting the time
    time get port Time
    
    @ Telemetry Port
    telemetry port Tlm

    # Commands
    @ Command to start the ESP32
    async command ExperimentState(
        experimentState: ExperimentState
    ) \
    opcode 0x01

    # Events
    @ Report Experiment State
    event ExperimentStatus(
        experimentStatus: ExperimentState
    ) \
    severity activity high \
    format "The experiment is {}"

    @ I2C Configuation Failed
    event I2cTelemetryError(
        writeStatus: Drv.I2cStatus
    ) \
    severity warning high \
    format "I2C Error: Telemetry request failed with code {}"

    @ I2C Configuation Failed
    event I2cConfigError(
        writeStatus: Drv.I2cStatus
    ) \
    severity warning high \
    format "I2C Error: Write status failed with code {}"

    @ I2C Device was not taken out of sleep mode
    event I2cModeError(
        writeStatus: Drv.I2cStatus
    ) \
    severity warning high \
    format "I2C Error: Power mode failed to set up with code {}"

    # Telemetry
    @ TempData from ESP32
    telemetry tempData: TempData id 0 update on change
  }
}
