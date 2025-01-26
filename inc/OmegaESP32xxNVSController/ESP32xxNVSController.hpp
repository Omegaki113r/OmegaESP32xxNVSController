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
 * Last Modified: Monday, 27th January 2025 1:15:23 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string>

#include <esp_err.h>
#include <esp_partition.h>
#include <nvs.h>
#include <nvs_flash.h>

#include "OmegaUtilityDriver/UtilityDriver.hpp"

namespace Omega
{
    namespace NVS
    {
        OmegaStatus init();
        OmegaStatus init(const char *);
        OmegaStatus init(const std::string &);

        template <typename T>
        OmegaStatus write(const char *key, const T value)
        {
            OmegaStatus status = eFAILED;
            nvs_handle_t nvs_handle;
            if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
            {
                OMEGA_LOGE("nvs_open failed for key: %s", key);
                goto ret;
            }
            if (ESP_OK != nvs_set_blob(nvs_handle, key, &value, sizeof(T)))
            {
                OMEGA_LOGE("nvs_set_blob failed for key: %s", key);
                goto nvs_close;
            }
            if (ESP_OK != nvs_commit(nvs_handle))
            {
                OMEGA_LOGE("nvs_commit failed for key: %s", key);
                goto nvs_close;
            }
            status = eSUCCESS;
        nvs_close:
            nvs_close(nvs_handle);
        ret:
            return status;
        }

        template <typename T>
        OmegaStatus read(const char *key, T *value)
        {
            OmegaStatus status = eFAILED;
            nvs_handle_t nvs_handle;
            auto size = sizeof(T);
            if (NULL == value)
            {
                OMEGA_LOGE("value provided for key: %s was NULL", key);
                goto ret;
            }
            if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
            {
                OMEGA_LOGE("nvs_open failed for key: %s", key);
                goto nvs_close;
            }
            if (ESP_OK != nvs_get_blob(nvs_handle, key, value, &size))
            {
                OMEGA_LOGE("nvs_get_blob failed for key: %s", key);
                goto nvs_close;
            }
            status = eSUCCESS;
        nvs_close:
            nvs_close(nvs_handle);
        ret:
            return status;
        }

    } // namespace NVS
} // namespace Omega
