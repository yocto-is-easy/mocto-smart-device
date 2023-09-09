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
    
    int err = 0;

    printf(MSD_READY_MSG"\n");

    // wait for head unit write to serial
    vTaskDelay(DELAY_FOR_WIFI_CREDENTIALS_MS / portTICK_PERIOD_MS);

    msd_wifi_config_t msd_wifi_config = {0};
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

    printf(MSD_CONFIGURED_MSG"\n");

}
