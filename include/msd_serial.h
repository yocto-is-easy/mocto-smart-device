#ifndef MSD_SERIAL_H
#define MSD_SERIAL_H

/* Mocto smart device serial configurator
 * 
 * - Uses default ESP32 serial port.
 * - Reads credentials of Wifi
 */

#include "msd_wifi.h"

int msd_serial_read_wifi_credentials(msd_wifi_config_t* msd_serial_wifi_credentials);

#endif // MSD_SERIAL_H
