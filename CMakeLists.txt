idf_component_register(SRCS
    "mocto-smart-device.c"
    "msd_wifi.c"
    "msd_nvs.c"
    "msd_serial.c"

    INCLUDE_DIRS "include"
    REQUIRES esp_wifi nvs_flash
)
