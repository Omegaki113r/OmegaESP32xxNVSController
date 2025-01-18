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
 * Last Modified: Saturday, 18th January 2025 11:02:01 pm
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

#include "OmegaESP32xxNVSController.hpp"

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

        OmegaStatus write_int(const char *key, const int value)
        {
            OmegaStatus status = eFAILED;
            nvs_handle_t nvs_handle;
            u64 write_value = value;
            if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
            {
                OMEGA_LOGE("nvs_open failed for key: %s", key);
                goto ret;
            }
            if (ESP_OK != nvs_set_i64(nvs_handle, key, write_value))
            {
                OMEGA_LOGE("nvs_set_i64 failed for key: %s", key);
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
            OMEGA_LOGD("key: %s value: %d", key, value);
        ret:
            return status;
        }

        OmegaStatus write_int(const std::string &in_key, const int in_value) { return write_int(in_key.c_str(), in_value); }

        OmegaStatus read_int(const char *key, int *value)
        {
            OmegaStatus status = eFAILED;
            nvs_handle_t nvs_handle;
            esp_err_t err;
            i64 read_data = 0;
            if (NULL == value)
            {
                OMEGA_LOGE("value provided for key: %s was NULL", key);
                goto ret;
            }
            if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
            {
                OMEGA_LOGE("nvs_open failed for key: %s", key);
                goto ret;
            }
            if (ESP_OK != (err = nvs_get_i64(nvs_handle, key, &read_data)))
            {
                if (ESP_ERR_NVS_NOT_FOUND == err &&
                    ESP_OK != (err = nvs_set_i64(nvs_handle, key, 0)))
                {
                    OMEGA_LOGE("nvs_get_i64 failed for key: %s, err: %s", key, esp_err_to_name(err));
                    goto nvs_close;
                }
            }
            memcpy(value, &read_data, sizeof(int));
            status = eSUCCESS;
        nvs_close:
            nvs_close(nvs_handle);
            OMEGA_LOGD("key: \"%s\" value: %d", key, *value);
        ret:
            return status;
        }

        OmegaStatus read_int(const std::string &in_key, int *out_value) { return read_int(in_key.c_str(), out_value); }

        OmegaStatus write_float(const char *key, const float value)
        {
            OmegaStatus status = eFAILED;
            nvs_handle_t nvs_handle;
            i64 converted_data = 0;
            if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
                goto ret;
            memcpy(&converted_data, &value, sizeof(float));
            if (ESP_OK != nvs_set_i64(nvs_handle, key, converted_data))
                goto ret;
            if (ESP_OK != nvs_commit(nvs_handle))
                goto ret;
            nvs_close(nvs_handle);
            status = eSUCCESS;
            OMEGA_LOGD("key: %s value: %f", key, value);
        ret:
            return status;
        }

        OmegaStatus write_float(const std::string &in_key, const float in_value) { return write_float(in_key.c_str(), in_value); }

        OmegaStatus read_float(const char *key, float *value)
        {
            OmegaStatus status = eFAILED;
            nvs_handle_t nvs_handle;
            i64 read_data = 0;
            if (ESP_OK != nvs_open("storage", NVS_READONLY, &nvs_handle))
                goto ret;
            if (ESP_OK != nvs_get_i64(nvs_handle, key, &read_data))
                goto ret;
            memcpy(value, &read_data, sizeof(i64));
            nvs_close(nvs_handle);
            status = eSUCCESS;
            OMEGA_LOGD("key: %s value: %f", key, *value);
        ret:
            return status;
        }

        OmegaStatus read_float(const std::string &in_key, float *out_value) { return read_float(in_key.c_str(), out_value); }
    } // namespace NVS
} // namespace Omega