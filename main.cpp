#include "BQ76952.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void outputGainTest(BQ76952& bms)
{
    bms.setVoltageGain(1, 20000); 
    std::this_thread::sleep_for(10ms);

    const uint16_t gain_voltage = bms.getCellVoltage(1);

    bms.setVoltageGain(1, 0); // reset the gain
    std::this_thread::sleep_for(10ms);

    const uint16_t normal_voltage = bms.getCellVoltage(1);

    std::cout << "The cell voltage before applying the gain: " << normal_voltage << ". After applying the gain: " << gain_voltage << '\n';
}

void outputDeviceID(BQ76952& bms)
{
    const uint16_t device_number = bms.getDeviceNumber();
    const uint16_t firmware_version = bms.getFWVersion();
    const uint16_t hardware_version = bms.getHWVersion();

    std::cout << "Device number 0x" << std::hex << device_number << '\n';
    std::cout << "Firmware version 0x" << std::hex <<  firmware_version << '\n';
    std::cout << "Hardware version 0x" << std::hex <<  hardware_version << '\n';
}


void outputVoltageTest(BQ76952& bms)
{
    const std::vector<uint16_t> voltages = bms.getAllVoltages();
    for(uint32_t i = 0; i < voltages.size(); i++)
    {
        if(i < 16)
            std::cout << "Cell Voltage" << i+1 << ":" << voltages[i] << '\n';     
        else if(i == 16)
            std::cout << "Stack Voltage: " << voltages[i] << '\n';
        else if(i == 17)
            std::cout << "Pack Voltage: " << voltages[i] << '\n';
        else
            std::cout << "LD Pin Voltage " << voltages[i] << '\n'; 
    }
}

void outputInternalTemperature(BQ76952& bms)
{
    const uint16_t temperature = bms.getThermistorTemp(INT_TEMP);
    std::cout << "Raw internal temperature " << temperature << '\n'; 
}



int main(void)
{
    BQ76952 bms("/dev/i2c-0", 0x08);

    outputDeviceID(bms);
    outputGainTest(bms);
    outputVoltageTest(bms);
    outputInternalTemperature(bms);

    return 0;
}
