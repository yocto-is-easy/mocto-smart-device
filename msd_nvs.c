#include "msd_nvs.h"

#include "nvs_flash.h"

void init_nvs() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    printf("Non-volatile storage flash has been initialized: %s\n", esp_err_to_name(ret));
}