#include "msd_serial.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "esp_log.h"

/* 
 * SSID Naming Conventions
 * https://www.cisco.com/assets/sol/sb/WAP321_Emulators/WAP321_Emulator_v1.0.0.3/help/Wireless05.html
 */

/* Wifi credentials getter
 *
 * reads string that looks like this:
 * [ssid$password]
 */ 
int msd_serial_read_wifi_credentials(msd_wifi_config_t* msd_serial_wifi_credentials) {
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    fgets(buffer, sizeof(buffer), stdin);

    if(strlen(buffer) == 0) {
        ESP_LOGE("msd_serial_read_wifi_credentials", "No input");
        return -1;
    }

    char* ssid_start = strchr(buffer, '[');
    char* ssid_end = strchr(buffer, '$');
    char* password_start = strchr(buffer, '$');
    char* password_end = strrchr(buffer, ']');

    if(ssid_start == NULL || ssid_end == NULL || password_start == NULL || password_end == NULL) {
        ESP_LOGE("msd_serial_read_wifi_credentials", "Invalid input format");
        return -1;
    }

    int ssid_length = ssid_end - ssid_start - 1;
    int password_length = password_end - password_start - 1;

    if(ssid_length > SSID_MAX_LENGTH) {
        ESP_LOGE("msd_serial_read_wifi_credentials", "SSID too long");
        return -2;
    }

    if(password_length > PASSWORD_MAX_LENGTH) {
        ESP_LOGE("msd_serial_read_wifi_credentials", "Password too long");
        return -3;
    }

    memcpy(msd_serial_wifi_credentials->ssid, ssid_start + 1, ssid_length);
    memcpy(msd_serial_wifi_credentials->password, password_start + 1, password_length);

    msd_serial_wifi_credentials->ssid[ssid_length] = '\0';
    msd_serial_wifi_credentials->password[password_length] = '\0';

    return 0;
}
