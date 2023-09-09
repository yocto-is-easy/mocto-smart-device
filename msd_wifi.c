#include "msd_wifi.h"

// requires NVS to be initialized
void wifi_init_connection(msd_wifi_config_t *msd_wifi_config) {
    esp_netif_init(); // initialize TCP/IP stack

    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    if(msd_wifi_config->wifi_event_handler != NULL) {
        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, msd_wifi_config->wifi_event_handler, NULL);
    }

    if(msd_wifi_config->ip_event_handler != NULL) {
        esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, msd_wifi_config->ip_event_handler, NULL);
    }

    wifi_config_t wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config_t));
    memcpy(wifi_config.sta.ssid, msd_wifi_config->ssid, sizeof(wifi_config.sta.ssid));
    memcpy(wifi_config.sta.password, msd_wifi_config->password, sizeof(wifi_config.sta.password));

    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());
}
