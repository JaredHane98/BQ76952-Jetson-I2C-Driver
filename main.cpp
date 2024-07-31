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

    std::cout << "Cell Voltage before gain " << normal_voltage << ". After gain " << gain_voltage << '\n';
}

void outputDeviceID(BQ76952& bms)
{
    const uint16_t device_number = bms.getDeviceNumber();
    const uint16_t firmware_version = bms.getFWVersion();
    const uint16_t hardware_version = bms.getHWVersion();

    std::cout << "Device number " << device_number << '\n';
    std::cout << "Firmware version " << firmware_version << '\n';
    std::cout << "Hardware version " << hardware_version << '\n';
}



int main(void)
{
    BQ76952 bms("/dev/i2c-0", 0x08);

    outputDeviceID(bms);
    outputGainTest(bms);


    //bms.setVoltageGain(1, 20000); 

    // std::vector<uint16_t> voltages = bms.getAllVoltages(); 

    // for(uint32_t i = 0; i < voltages.size(); i++)
    //     std::cout << "Voltage " << i+1 << ": " <<  voltages[i] << '\n';

    // bms.setVoltageGain(1, 0);  
    

    // while(true)
    // {
    //     const uint16_t cell_voltage = bms.getCellVoltage(1);
    //     const uint16_t pack_voltage = bms.getPackVoltage();
    //     const uint16_t ld_voltage = bms.getLDVoltage();
    //     const uint16_t thermistor_temp = bms.getThermistorTemp(INT_TEMP);
    //     std::cout << cell_voltage << " " << pack_voltage << " " << ld_voltage << " " << thermistor_temp << '\n';
    // }

    return 0;
}
