/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp32/rom/uart.h"

// Generics
#define LOG_TAG "app"

// Pins
#define BLINK_GPIO_PIN         GPIO_NUM_2

void TaskDelayMs(int ms)
{
    vTaskDelay(ms/portTICK_PERIOD_MS);
}

void hearbeat_task(void * pvParameter)
{
    gpio_reset_pin(BLINK_GPIO_PIN);
    gpio_set_direction(BLINK_GPIO_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        TaskDelayMs(1000);
        gpio_set_level(BLINK_GPIO_PIN, 0);
        TaskDelayMs(1000);
        gpio_set_level(BLINK_GPIO_PIN, 1);
    }
}

void app_main(void)
{
    ESP_LOGI(LOG_TAG, "Initializing ESP32\n");
    xTaskCreate(&hearbeat_task, "hearbeat_task", 2048, NULL, 5, NULL);
}

