#include "msd_wifi.h"

void wifi_event_handler(void* arg, esp_event_base_t event_base,
                        int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_STA_START) {
        printf("wifi_event_handler: WIFI_EVENT_STA_START\n");
        esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
        printf("wifi_event_handler: WIFI_EVENT_STA_DISCONNECTED\n");
        esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_CONNECTED) {
        printf("wifi_event_handler: WIFI_EVENT_STA_CONNECTED\n");
    } else if (event_id == WIFI_EVENT_STA_STOP) {
        printf("wifi_event_handler: WIFI_EVENT_STA_STOP\n");
    }
}

void ip_event_handler(void* arg, esp_event_base_t event_base,
                      int32_t event_id, void* event_data) {
    if (event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        printf("ip_event_handler: IP_EVENT_STA_GOT_IP\n");
    }
}

// requires NVS to be initialized
int msd_wifi_init_connection(msd_wifi_config_t *msd_wifi_config) {
    int err = 0;
    
    err = esp_netif_init(); // initialize TCP/IP stack
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_netif_init failed: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_event_loop_create_default();
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_event_loop_create_default failed: %s", esp_err_to_name(err));
        return err;
    }
    
    // TODO: research why does works even with error return
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    err = esp_wifi_init(&cfg);
    if(err != ESP_OK) {
        return err;
    }

    // TODO: add here custom handles
    err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_event_handler_register failed: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL);
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_event_handler_register failed: %s", esp_err_to_name(err));
        return err;
    }

    wifi_config_t wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config_t));
    memcpy(wifi_config.sta.ssid, msd_wifi_config->ssid, sizeof(wifi_config.sta.ssid));
    memcpy(wifi_config.sta.password, msd_wifi_config->password, sizeof(wifi_config.sta.password));

    err = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_wifi_set_config failed: %s", esp_err_to_name(err));
        return err;
    }
    err = esp_wifi_start();
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_wifi_start failed: %s", esp_err_to_name(err));
        return err;
    }
    err = esp_wifi_connect();
    if(err != ESP_OK) {
        ESP_LOGE("msd_wifi_init_connection", "esp_wifi_connect failed: %s", esp_err_to_name(err));
        return err;
    }

    return 0;
}
