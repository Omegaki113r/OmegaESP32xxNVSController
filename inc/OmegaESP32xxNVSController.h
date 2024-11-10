/**
 * @file OmegaESP32xxNVSController.h
 * @author Omegaki113r
 * @date Sunday, 10th November 2024 7:02:51 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32xxNVSController
 * File Name: OmegaESP32xxNVSController.h
 * File Created: Sunday, 10th November 2024 7:02:51 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Sunday, 10th November 2024 10:03:12 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef __OMEGA_ESP32xx_NVS_CONTROLLER_H__
#define __OMEGA_ESP32xx_NVS_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include "OmegaUtilityDriver.h"

    OmegaStatus OmegaESP32xxNVSController_init();
    OmegaStatus OmegaESP32xxNVSController_write_int(const char *key, const int value);
    OmegaStatus OmegaESP32xxNVSController_read_int(const char *key, int *value);
    OmegaStatus OmegaESP32xxNVSController_write_float(const char *key, const float value);
    OmegaStatus OmegaESP32xxNVSController_read_float(const char *key, float *value);
#ifdef __cplusplus
}
#endif

#endif