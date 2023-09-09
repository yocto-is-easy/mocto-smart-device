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

typedef struct msd_wifi_config {
    char ssid[256];
    char password[256];
    void (*wifi_event_handler)(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data);
    void (*ip_event_handler)(void* arg, esp_event_base_t event_base,
                             int32_t event_id, void* event_data);
} msd_wifi_config_t;

void wifi_init_connection(msd_wifi_config_t* msd_wifi_config);

#endif // MSD_WIFI_H
