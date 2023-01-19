module Power {
    @ System power modes
    enum powerModes {
        Startup
        Idle
        Safe
        Experiment
        Transmit
        Deorbit
    }

    @ Types of system failure
    enum failType {
        type1 = 1 @< TODO
        type2 = 2
        type3 = 3
        type4 = 4
    }

    @ Actions that may be required upon system failure
    enum requestedAction {
        action1 @< TODO
        action2
        action3
        action4
    } default action1

    @ Array to hold StarBuck Nano temperature values 
    array sbnTemps = [6] I8

    @ Struct for sending power mode changes
    struct PwrMode {
        pwrMode: powerModes
        Tc: Fw.Time @< see sdd.md
    }

    @ Struct for receiving safe mode requests
    struct FailRequest {
        failure: failType
        action: requestedAction
        Tc: Fw.Time @< see sdd.md
    }

    @ Struct for sending StarBuck Nano telemetry
    struct SystemInfo {
        solarPower: I8
        battLevels: I8
        sysTemp: sbnTemps
    }

    @ Component for controlling power modes and interfacing with the StarBuck Nano
    active component SBNController {
        # ----------------------------------------------------------------------
        # General ports
        # ----------------------------------------------------------------------

        @ Sends current power mode to other components
        output port pwrMode: PwrMode

        @ Recieves safe mode requests
        input port pwrFail: FailRequest

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

        @ Command to set the power mode of all components
        async command setPowerMode (
            pwrMode: PwrMode @< system power mode
            ) \
        opcode 0x01

        @ Command to request system to go into safe mode
        async command criticalCondition (
            FailRequest: FailRequest @< type of system failure
            ) \
        opcode 0x02

        @ Command to reset the StarBuck Nano
        async command resetSBN () \
        opcode 0x03

        @ command to request the StarBuck Nano to go into sleep mode
        async command sleepSBN () \
        opcode 0x04

        # ----------------------------------------------------------------------
        # Events
        # ----------------------------------------------------------------------

        @ Event for when the power mode is changed
        event currentPowerMode(
            pwrMode: powerModes @< power mode that was set
        ) \
        severity activity high \
        id 0 \
        format "System power mode set to {}"

        @ Event for when a critical error is reported
        event criticalError(
            failType: failType @< type of system failure
        ) \
        severity warning high \
        id 1 \
        format "System power mode set to {}"

        @ I2C Configuation Failed
        event I2cTelemetryError(
            writeStatus: Drv.I2cStatus
        ) \
        severity warning high \
        id 2 \
        format "I2C Error: Telemetry request failed with code {}"

        @ I2C Configuation Failed
        event I2cConfigError(
            writeStatus: Drv.I2cStatus
        ) \
        severity warning high \
        id 3 \
        format "I2C Error: Write status failed with code {}"

        @ I2C Device was not taken out of sleep mode
        event I2cModeError(
            writeStatus: Drv.I2cStatus
        ) \
        severity warning high \
        id 4 \
        format "I2C Error: Power mode failed to set up with code {}"

        # ----------------------------------------------------------------------
        # Telemetry
        # ----------------------------------------------------------------------

        @ Power telemetry from StarBuck Nano
        telemetry systemInfo: SystemInfo \
        id 0 \
        update on change

    }

}