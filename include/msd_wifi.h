#ifndef MSD_WIFI_H
#define MSD_WIFI_H

#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "freertos/event_groups.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_netif.h"

#include "memory.h"

#define SSID_MAX_LENGTH 32
#define PASSWORD_MAX_LENGTH 64

typedef struct msd_wifi_config {
    char ssid[SSID_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} msd_wifi_config_t;

int msd_wifi_init_connection(msd_wifi_config_t *msd_wifi_config);

#endif // MSD_WIFI_H
