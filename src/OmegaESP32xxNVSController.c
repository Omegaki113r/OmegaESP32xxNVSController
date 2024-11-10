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
 * Last Modified: Sunday, 10th November 2024 10:07:48 pm
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

#include "OmegaESP32xxNVSController.h"

OmegaStatus OmegaESP32xxNVSController_init(const char *nvs_partition_label)
{
    OmegaStatus status = eFAILED;
    esp_partition_t *partition;
    if (NULL != (partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, nvs_partition_label)))
    {
        esp_err_t err = nvs_flash_init_partition(partition->label);
        if (ESP_ERR_NVS_NO_FREE_PAGES == err || ESP_ERR_NVS_NEW_VERSION_FOUND == err)
        {
            if (ESP_OK != nvs_flash_erase())
                goto ret;
            if (ESP_OK != nvs_flash_init_partition(partition->label))
                goto ret;
        }
        status = eSUCCESS;
    }
ret:
    return status;
}

OmegaStatus OmegaESP32xxNVSController_write_int(const char *key, const int value)
{
    OmegaStatus status = eFAILED;
    nvs_handle_t nvs_handle;
    if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
        goto ret;
    if (ESP_OK != nvs_set_i64(nvs_handle, key, value))
        goto ret;
    if (ESP_OK != nvs_commit(nvs_handle))
        goto ret;
    nvs_close(nvs_handle);
    status = eSUCCESS;
ret:
    return status;
}

OmegaStatus OmegaESP32xxNVSController_read_int(const char *key, int *value)
{
    OmegaStatus status = eFAILED;
    nvs_handle_t nvs_handle;
    if (ESP_OK != nvs_open("storage", NVS_READONLY, &nvs_handle))
        goto ret;
    if (ESP_OK != nvs_get_i64(nvs_handle, key, (i64 *)value))
        goto ret;
    nvs_close(nvs_handle);
    status = eSUCCESS;
ret:
    return status;
}

OmegaStatus OmegaESP32xxNVSController_write_float(const char *key, const float value)
{
    OmegaStatus status = eFAILED;
    nvs_handle_t nvs_handle;
    if (ESP_OK != nvs_open("storage", NVS_READWRITE, &nvs_handle))
        goto ret;
    i64 converted_data = 0;
    memcpy(&converted_data, &value, sizeof(float));
    if (ESP_OK != nvs_set_i64(nvs_handle, key, converted_data))
        goto ret;
    if (ESP_OK != nvs_commit(nvs_handle))
        goto ret;
    nvs_close(nvs_handle);
    status = eSUCCESS;
ret:
    return status;
}

OmegaStatus OmegaESP32xxNVSController_read_float(const char *key, float *value)
{
    OmegaStatus status = eFAILED;
    nvs_handle_t nvs_handle;
    if (ESP_OK != nvs_open("storage", NVS_READONLY, &nvs_handle))
        goto ret;
    i64 read_data = 0;
    if (ESP_OK != nvs_get_i64(nvs_handle, key, &read_data))
        goto ret;
    memcpy(value, &read_data, sizeof(i64));
    nvs_close(nvs_handle);
    status = eSUCCESS;
ret:
    return status;
}