// Basic configuration file for the project

#pragma once

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_mac.h"
#include "esp_chip_info.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"

// Pin Configurations

// I2S Configuration
#define I2S_BLK_PIN GPIO_NUM_5
#define I2S_WS_PIN GPIO_NUM_19
#define I2S_DATA_OUT_PIN GPIO_NUM_23
#define I2S_DATA_IN_PIN I2S_GPIO_UNUSED
#define I2S_SCLK_PIN I2S_GPIO_UNUSED

// SDMMC Configuration (default for ESP32-WROVER-E)
#define SDMMC_CMD_PIN GPIO_PIN_15
#define SDMMC_CLK_PIN GPIO_PIN_14
#define SDMMC_D0_PIN GPIO_PIN_2
#define SDMMC_D1_PIN GPIO_PIN_4
#define SDMMC_D2_PIN GPIO_PIN_12
#define SDMMC_D3_PIN GPIO_PIN_13

void print_system_info(void)
{
  char TAG[] = "conf";
  // print idf version
  ESP_LOGI(TAG, "IDF version: %s", esp_get_idf_version());

  // show chip info
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  ESP_LOGI(TAG, "Chip Model: %s", CONFIG_IDF_TARGET);

  ESP_LOGI(TAG, "This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  ESP_LOGI(TAG, "silicon revision %d, ", chip_info.revision);

  // mac address
  uint8_t mac[6];
  esp_efuse_mac_get_default(mac);
  ESP_LOGI(TAG, "default mac: %02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}