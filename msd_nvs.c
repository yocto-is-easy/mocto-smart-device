#include "msd_nvs.h"

#include "nvs_flash.h"
#include "esp_log.h"

#define MSD_NVS_NAMESPACE "msd_nvs"
#define MSD_NVS_KEY_WIFI_SSID "ssid"
#define MSD_NVS_KEY_WIFI_PASSWORD "password"
#define MSD_NVS_KEY_WIFI_CONFIGURED "configured"

void msd_nvs_init(bool erase) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        if (erase) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ESP_LOGI("msd_nvs_init" ,"Non-volatile storage flash has been erased");
        }
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    ESP_LOGI("msd_nvs_init" ,"Non-volatile storage flash has been initialized");
}

int has_wifi_credentials() {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(MSD_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE("has_wifi_credentials", "nvs_open failed: %s", esp_err_to_name(err));
        return -1;
    }

    // check MSD_NVS_KEY_WIFI_CONFIGURED if 255
    uint8_t configured = 0;
    err = nvs_get_u8(nvs_handle, MSD_NVS_KEY_WIFI_CONFIGURED, &configured);
    if (err != ESP_OK) {
        ESP_LOGW("has_wifi_credentials", "nvs_get_u8 failed: %s", esp_err_to_name(err));
        return -2;
    }

    nvs_close(nvs_handle);

    if (configured == 255) {
        return 0;
    }
    return 1;
}

int msd_save_wifi_credentials(msd_wifi_config_t *msd_wifi_config) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(MSD_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE("msd_save_wifi_credentials", "nvs_open failed: %s", esp_err_to_name(err));
        return -1;
    }

    err = nvs_set_str(nvs_handle, MSD_NVS_KEY_WIFI_SSID, msd_wifi_config->ssid);
    if (err != ESP_OK) {
        ESP_LOGE("msd_save_wifi_credentials", "nvs_set_str failed set ssid: %s", esp_err_to_name(err));
        return -2;
    }

    err = nvs_set_str(nvs_handle, MSD_NVS_KEY_WIFI_PASSWORD, msd_wifi_config->password);
    if (err != ESP_OK) {
        ESP_LOGE("msd_save_wifi_credentials", "nvs_set_str failed set password: %s", esp_err_to_name(err));
        return -3;
    }

    err = nvs_set_u8(nvs_handle, MSD_NVS_KEY_WIFI_CONFIGURED, 255);
    if (err != ESP_OK) {
        ESP_LOGE("msd_save_wifi_credentials", "nvs_set_u8 failed wifi configured flag: %s", esp_err_to_name(err));
        return -4;
    }

    err = nvs_commit(nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE("msd_save_wifi_credentials", "nvs_commit failed: %s", esp_err_to_name(err));
        return -5;
    }

    nvs_close(nvs_handle);

    return 0;
}

int msd_load_wifi_credentials(msd_wifi_config_t *msd_wifi_config) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(MSD_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE("msd_load_wifi_credentials", "nvs_open failed: %s", esp_err_to_name(err));
        return -1;
    }

    size_t ssid_length = SSID_MAX_LENGTH;
    err = nvs_get_str(nvs_handle, MSD_NVS_KEY_WIFI_SSID, msd_wifi_config->ssid, &ssid_length);
    if (err != ESP_OK) {
        ESP_LOGE("msd_load_wifi_credentials", "nvs_get_str failed: %s", esp_err_to_name(err));
        return -2;
    }

    size_t password_length = PASSWORD_MAX_LENGTH;
    err = nvs_get_str(nvs_handle, MSD_NVS_KEY_WIFI_PASSWORD, msd_wifi_config->password, &password_length);
    if (err != ESP_OK) {
        ESP_LOGE("msd_load_wifi_credentials", "nvs_get_str failed: %s", esp_err_to_name(err));
        return -3;
    }

    nvs_close(nvs_handle);

    return 0;
}
