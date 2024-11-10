# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

add_compile_definitions(CONFIG_OMEGA_LOGGING=1 BUILD_TESTING=0)

set(OMEGA_ESP32NVS_CONTROLLER_LIB ../..)

set(EXTRA_COMPONENT_DIRS ${OMEGA_ESP32NVS_CONTROLLER_LIB})

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(nvs-test)
