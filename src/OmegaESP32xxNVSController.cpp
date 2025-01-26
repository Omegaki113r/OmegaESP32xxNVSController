/**
 * @file OmegaESP32xxNVSController.c
 * @author Omegaki113r
 * @date Sunday, 10th November 2024 7:00:27 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32xxNVSController
 * File Name: OmegaESP32xxNVSController.c
 * File Created: Sunday, 10th November 2024 7:00:27 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Monday, 27th January 2025 1:11:07 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#include <string.h>

#include <esp_err.h>
#include <esp_partition.h>
#include <nvs.h>
#include <nvs_flash.h>

#include "OmegaESP32xxNVSController/ESP32xxNVSController.hpp"

namespace Omega
{
    namespace NVS
    {
        OmegaStatus init()
        {
            auto err = nvs_flash_init();
            if (ESP_ERR_NVS_NO_FREE_PAGES == err || ESP_ERR_NVS_NEW_VERSION_FOUND == err)
            {
                if (ESP_OK != nvs_flash_erase())
                    return eFAILED;
                if (ESP_OK != nvs_flash_init())
                    return eFAILED;
            }
            else if (ESP_OK == err)
            {
                return eSUCCESS;
            }
            return eFAILED;
        }

        OmegaStatus init(const char *nvs_partition_label)
        {
            if (const auto partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, nvs_partition_label); nullptr != partition)
            {
                esp_err_t err = nvs_flash_init_partition(partition->label);
                if (ESP_ERR_NVS_NO_FREE_PAGES == err || ESP_ERR_NVS_NEW_VERSION_FOUND == err)
                {
                    if (ESP_OK != nvs_flash_erase())
                        return eFAILED;
                    if (ESP_OK != nvs_flash_init_partition(partition->label))
                        return eFAILED;
                }
                return eSUCCESS;
            }
            return eFAILED;
        }

        OmegaStatus init(const std::string &in_nvs_partition_label) { return init(in_nvs_partition_label.c_str()); }

    } // namespace NVS
} // namespace Omega