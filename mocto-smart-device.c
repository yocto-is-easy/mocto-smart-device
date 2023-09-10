#include <stdio.h>
#include "mocto-smart-device.h"

#define MSD_READY_MSG "MSD_READY"
#define MSD_CONFIGURED_MSG "MSD_CONFIGURED_MSG"
#define MSD_ERROR_MSG "MSD_ERROR"
#define MSD_ERROR_READING_WIFI_CREDENTIALS_MSG "MSD_ERROR_READING_WIFI_CREDENTIALS"
#define MSD_ERROR_WIFI_INIT_MSG "MSD_ERROR_WIFI_INIT"

#define DELAY_FOR_WIFI_CREDENTIALS_MS 200

void msd_configure() {
    msd_nvs_init(false);

    msd_wifi_config_t msd_wifi_config = {0};

    // check NVS has wifi credentials
    if(has_wifi_credentials() == 0) {
        // then get values from NVS and return
        
        int err = msd_load_wifi_credentials(&msd_wifi_config);
        if(err != 0) {
            ESP_LOGE("msd_configure", "msd_load_wifi_credentials failed: %s", esp_err_to_name(err));
            return;
        }

        err = msd_wifi_init_connection(&msd_wifi_config);
        if(err != 0) {
            ESP_LOGE("msd_configure", "msd_wifi_init_connection failed: %s", esp_err_to_name(err));
            return;
        }

        ESP_LOGI("msd_configure", "Wifi configured from NVS with ssid: %s", msd_wifi_config.ssid);

    } else {
        int err = 0;
        printf(MSD_READY_MSG"\n");

        // wait for head unit write to serial
        vTaskDelay(DELAY_FOR_WIFI_CREDENTIALS_MS / portTICK_PERIOD_MS);

        err = msd_serial_read_wifi_credentials(&msd_wifi_config);
        if(err != 0) {
            printf(MSD_ERROR_READING_WIFI_CREDENTIALS_MSG"\n");
            return;
        }

        err = msd_wifi_init_connection(&msd_wifi_config);
        if(err != 0) {
            printf(MSD_ERROR_WIFI_INIT_MSG"\n");
            return;
        }

        err = msd_save_wifi_credentials(&msd_wifi_config);
        if(err != 0) {
            printf(MSD_ERROR_MSG"\n");
            return;
        }

        printf(MSD_CONFIGURED_MSG"\n");
    }
}
