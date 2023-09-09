#include "msd_nvs.h"

#include "nvs_flash.h"
#include "esp_log.h"

void msd_nvs_init(bool erase) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        if (erase) {
            ESP_ERROR_CHECK(nvs_flash_erase());
        }
        ret = nvs_flash_init();
    }

    ESP_LOGI("msd_nvs_init" ,"Non-volatile storage flash has been initialized");
}