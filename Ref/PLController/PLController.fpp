module Payload {
    @ Array to hold temperature data from all sensors
    array tempData = [16] I32

    @ Array to hold wattages for both heaters
    array heaterData = [2] U8

    @ Array to hold expected wattage levels for all Tc of experiment
    array tcWatt = [256] U8
    
    @ Type for periodical status updates
    struct StatusUpdate {
        rawTemp: tempData
        rawBatt: I8
        heaterWatt: heaterData
    }

    @ Type for experiment result data
    struct ExpResult {
        rawTemp: tempData
        rawBatt: I8
        heaterWatt: heaterData
    }

    @ Type for experiment parameters
    struct ExpParams {
        expLength: U8
        expWattInt: tcWatt
        expWattDec: tcWatt
    }

    @ Component for processing raw temperature data
    active component PLController {
        # ----------------------------------------------------------------------
        # General ports
        # ----------------------------------------------------------------------

        @ Sends experiment result data to be processed
        sync input port TemperatureData: tempData

        @ Port that reads data from ESP32
        output port read: Drv.I2c

        @ Port that writes data to ESP32
        output port write: Drv.I2c

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

        @ Command to tell ESP32 to begin experiment
        async command ExpStart (
            expParams: ExpParams @< Experiment parameters
            ) \
        opcode 0x01

        @ Command to tell ESP32 to halt experiment
        async command ExpStop (
            stopType: bool @< should the experiment stop immediately or after current increment test
        ) \
        opcode 0x02

        @ Command to configure the experiment parameters
        async command ExpConfig (
            expParams: ExpParams @< Experiment parameters
        ) \
        opcode 0x03

        @ Command to request a payload status update from the ESP32
        sync command PLStatus () \
        opcode 0x04

        @ Command to request the experiment results
        sync command ExpResults () \
        opcode 0x05

        # ----------------------------------------------------------------------
        # Events
        # ----------------------------------------------------------------------

        @ Event for when an experiment successfully finishes
        event ExperimentComplete(
            expLength: U8 @< Configured length of experiment
        ) \
        severity activity high \
        id 0 \
        format "Payload experiment of {} minutes completed successfully"

        @ Event for when the payload sends a status update
        event PayloadUpdates() \
        severity activity low \
        id 1 \
        format "Payload update received"

        @ Event for high temperature
        event PayloadOverheat() \
        severity warning high \
        id 2 \
        format "High payload temperatures"

        @ Warning for faulty heater
        event PayloadHeaterError(
            heaterID: U8 @< which heater is not functioning correctly
        ) \
        severity warning low \
        id 3 \
        format "Heater {} not functioning correctly"

        @ Warning for faulty temperature sensor
        event PayloadSensorError(
            sensorID: U8 @< which sensor is not functioning correctly
        ) \
        severity warning low \
        id 4 \
        format "Sensor {} not functioning correctly"

        @ I2C Configuration Failed
        event I2cTelemetryError(
            writeStatus: Drv.I2cStatus
        ) \
        severity warning high \
        id 5 \
        format "I2C Error: Telemetry request failed with code {}"

        @ I2C Configuration Failed
        event I2cConfigError(
            writeStatus: Drv.I2cStatus
        ) \
        severity warning high \
        id 6 \
        format "I2C Error: Write status failed with code {}"

        @ I2C Device was not taken out of sleep mode
        event I2cModeError(
            writeStatus: Drv.I2cStatus
        ) \
        severity warning high \
        id 7 \
        format "I2C Error: Power mode failed to set up with code {}"

        # ----------------------------------------------------------------------
        # Telemetry
        # ----------------------------------------------------------------------

        @ Total number of experiments completed
        telemetry payloadStatus: StatusUpdate \
        id 0 \
        update on change

    }
}