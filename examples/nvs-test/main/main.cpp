#include <stdio.h>

#include <esp_err.h>

#include "OmegaESP32xxNVSController/ESP32xxNVSController.hpp"
#include "OmegaUtilityDriver/UtilityDriver.hpp"

extern "C" void app_main(void)
{
    if (eSUCCESS != Omega::NVS::init(nullptr))
        OMEGA_LOGE("NVS Controller initialization failed");
    struct s
    {
        int write = 0;
        int read = 0;
        float writef = 0;
        float readf = 0;
    };
    s data;
    for (;;)
    {
        data.write += 1;
        data.writef += 1.0f;
        Omega::NVS::write("data", data.write);
        Omega::NVS::read("data", &data.read);
        OMEGA_LOGI("Write Value: %.2d Read value: %.2d", data.write, data.read);
        Omega::NVS::write("dataf", data.writef);
        Omega::NVS::read("dataf", &data.readf);
        OMEGA_LOGI("Write Value: %.2f Read value: %.2f", data.writef, data.readf);
        delay_ms(100);
    }
}
