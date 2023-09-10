#include "msd_blinker.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define BLINK_GPIO GPIO_NUM_2
#define DELAY_BETWEEN_BLINKS_MS (500 / portTICK_PERIOD_MS)
#define LONG_BLINK_DELAY_MS (500 / portTICK_PERIOD_MS)
#define SHORT_BLINK_DELAY_MS (100 / portTICK_PERIOD_MS)
#define HIGH 1
#define LOW 0

void msd_blinker_init() {
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void short_blink() {
    gpio_set_level(BLINK_GPIO, HIGH);
    vTaskDelay(SHORT_BLINK_DELAY_MS);
    gpio_set_level(BLINK_GPIO, LOW);
}

void long_blink() {
    gpio_set_level(BLINK_GPIO, HIGH);
    vTaskDelay(LONG_BLINK_DELAY_MS);
    gpio_set_level(BLINK_GPIO, LOW);
}

void msd_notify_wifi_configured_from_serial() {
    short_blink();
    vTaskDelay(DELAY_BETWEEN_BLINKS_MS);
    short_blink();
    vTaskDelay(DELAY_BETWEEN_BLINKS_MS);
    long_blink();
}

void msd_notify_wifi_configured_from_nvs() {
    short_blink();
    vTaskDelay(DELAY_BETWEEN_BLINKS_MS);
    long_blink();
}
