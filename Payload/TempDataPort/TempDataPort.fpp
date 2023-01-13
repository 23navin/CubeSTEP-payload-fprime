module TempDataPort {
    struct TemperatureData{
        Temp_Far: [16] I32 @< 32 signed bit for temperature Fahrenheit
        Temp_Cel: [16] I32 @< 32 signed bit for temperature Celsius
        Watt_Data: U32
        @ imgData: Fw.Buffer @< buffer that contains image data
    }

    @ Port for receiving temp data. NOTE: Always have tempData
    port tempData(
        ref tempData: TemperatureData @< Port that carries raw temp data
    )
}