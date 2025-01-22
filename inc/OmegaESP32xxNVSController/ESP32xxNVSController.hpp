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
 * Last Modified: Wednesday, 22nd January 2025 10:21:41 pm
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

#include "OmegaUtilityDriver/UtilityDriver.hpp"

namespace Omega
{
    namespace NVS
    {
        OmegaStatus init();
        OmegaStatus init(const char *);
        OmegaStatus init(const std::string &);
        OmegaStatus write_int(const char *, const int);
        OmegaStatus write_int(const std::string &, const int);
        OmegaStatus read_int(const char *, int *);
        OmegaStatus read_int(const std::string &, int *);
        OmegaStatus write_float(const char *, const float);
        OmegaStatus write_float(const std::string &, const float);
        OmegaStatus read_float(const char *, float *);
        OmegaStatus read_float(const std::string &, float *);
    } // namespace NVS
} // namespace Omega
