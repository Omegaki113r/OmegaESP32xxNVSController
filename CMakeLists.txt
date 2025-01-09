set(SOURCES src/OmegaESP32xxNVSController.cpp)
set(PUBLIC_HEADER_DIRS inc)
set(PRIVATE_HEADER_DIRS priv/inc)

idf_component_register(
                        SRCS ${SOURCES}
                        INCLUDE_DIRS ${PUBLIC_HEADER_DIRS}
                        REQUIRES driver nvs_flash esp_partition OmegaUtilityDriver
                        )