/**
 * @file app_main.c
 *
 * @brief WiFi station mode example.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <stdio.h>

#include "server.h"
#include "temp_sensor.h"
//---------------------------------- MACROS -----------------------------------
#define EXAMPLE_ESP_WIFI_SSID ("ZICER-guest")
#define EXAMPLE_ESP_WIFI_PASS ("Z1c3r.10020")

#define DELAY_TIME_MS (5000U)

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief It's a callback function that is called when an event occurs.
 *
 * @param [in] p_arg This is a pointer to the argument passed to the event handler.
 * @param [in] event_base The event base that the event is associated with.
 * @param [in] event_id The event ID.
 * @param [in] p_event_data This is the data that is passed to the event handler.
 */
static void _event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data);

/**
 * @brief It sets up the ESP32 as a station.
 *
 * @return The error code of the last function call.
 */
static esp_err_t _wifi_init_sta(void);

/**
 * @brief If the NVS partition is not initialized, initialize it.
 *
 * @return The return value is the bitwise OR of the return values of nvs_flash_erase() and
 * nvs_flash_init().
 */
static esp_err_t _nvs_init(void);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static const char *TAG = "WIFI";

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

void app_main(void)
{
    esp_err_t err = ESP_OK;


    /* Initialize NVS partition */
    err = _nvs_init();

    if(ESP_OK == err)
    {
        /* Initialize TCP/IP */
        ESP_LOGI(TAG, " Initialize TCP/IP");
        err = esp_netif_init();
    }

    if(ESP_OK == err)
    {
        /* Initialize the event loop */
        ESP_LOGI(TAG, " Initialize the event loop");
        err = esp_event_loop_create_default();
    }

    if(ESP_OK == err)
    {
        /* Register our event handler for Wi-Fi and IP and related events */
        ESP_LOGI(TAG, " Register our event handler for Wi-Fi");
        err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &_event_handler, NULL);
    }

    if(ESP_OK == err)
    {
        /* Register our event handler for Wi-Fi and IP and related events */
        ESP_LOGI(TAG, " Register our event handler for IP and related events");
        err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &_event_handler, NULL);
    }

    if(ESP_OK == err)
    {
        /* Start the station */
        ESP_LOGI(TAG, " Start the station");
        err = _wifi_init_sta();
    }

    if(ESP_OK != err)
    {
        ESP_LOGE(TAG, "Init failed");
    }
    printf("esagluk: some_function\n");
    some_function();

    i2c_master_init();
    /* Do something */
    int index = 0;
    for(;;)
    {
        printf("[%d] WiFi Example!\n", index);
        index++;
        read_temp();
        vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

static esp_err_t _wifi_init_sta(void)
{
    esp_err_t err = ESP_OK;

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    err = esp_wifi_init(&cfg);

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "Set wifi credentials storage: RAM");
        err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    }

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "Set wifi mode: STATION");
        err = esp_wifi_set_mode(WIFI_MODE_STA);
    }

    wifi_config_t wifi_config = 
    {
      .sta =
          {
              .ssid = EXAMPLE_ESP_WIFI_SSID,
              .password = EXAMPLE_ESP_WIFI_PASS,
          },
    };

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "Configure wifi");
        err = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    }

    if(ESP_OK == err)
    {
        err = esp_wifi_start();
        ESP_LOGI(TAG, "Try to connect to AP with SSID:%s PSWD:%s", EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    }

    return err;
}

static esp_err_t _nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if((ESP_ERR_NVS_NO_FREE_PAGES == ret) || (ESP_ERR_NVS_NEW_VERSION_FOUND == ret))
    {
        /* NVS partition was truncated
         * and needs to be erased */
        ret = nvs_flash_erase();

        /* Retry nvs_flash_init */
        ret |= nvs_flash_init();
    }
    return ret;
}

//---------------------------- INTERRUPT HANDLERS -----------------------------

static void _event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data)
{
    if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_START == event_id))
    {
        ESP_LOGI(TAG, "Try to connect.");
        esp_wifi_connect();
    }
    else if((IP_EVENT == event_base) && (IP_EVENT_STA_GOT_IP == event_id))
    {
        ip_event_got_ip_t *p_event = (ip_event_got_ip_t *)p_event_data;
        ESP_LOGI(TAG, "CONNECTED with IP Address:" IPSTR, IP2STR(&p_event->ip_info.ip));
        /* Signal main application to continue execution */
    }
    else if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_DISCONNECTED == event_id))
    {
        ESP_LOGI(TAG, "DISCONNECTED. \nReconnecting to the AP again...");
        esp_wifi_connect();
    }
}