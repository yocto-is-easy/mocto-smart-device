#ifndef MSD_NVS_H
#define MSD_NVS_H

#include <stdbool.h>
#include "msd_wifi.h"

void msd_nvs_init(bool erase);

int has_wifi_credentials();
int msd_save_wifi_credentials(msd_wifi_config_t *msd_wifi_config);
int msd_load_wifi_credentials(msd_wifi_config_t *msd_wifi_config);

#endif // MSD_NVS_H
