#include <stdio.h>

#include <esp_err.h>

#include "OmegaESP32xxNVSController.hpp"
#include "OmegaUtilityDriver.hpp"

extern "C" void app_main(void)
{
    if (eSUCCESS != OmegaESP32xxNVSController_init(nullptr))
        OMEGA_LOGE("NVS Controller initialization failed");
    int write = 0;
    int read = 0;
    float writef = 0;
    float readf = 0;
    for (;;)
    {
        write += 1;
        writef += 1.0f;
        OmegaESP32xxNVSController_write_int("data", write);
        OmegaESP32xxNVSController_read_int("data", &read);
        OMEGA_LOGI("Write Value: %.2d Read value: %.2d", write, read);
        OmegaESP32xxNVSController_write_float("dataf", writef);
        OmegaESP32xxNVSController_read_float("dataf", &readf);
        OMEGA_LOGI("Write Value: %.2f Read value: %.2f", writef, readf);
        delay_ms(100);
    }
}
