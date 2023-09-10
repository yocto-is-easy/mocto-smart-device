#ifndef MSD_BLINKER_H
#define MSD_BLINKER_H

#include <stdint.h>

#include "driver/gpio.h"

void msd_blinker_init();

void msd_notify_wifi_configured_from_serial();
void msd_notify_wifi_configured_from_nvs();

#endif // MSD_BLINKER_H
