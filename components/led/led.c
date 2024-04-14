/**
 * @file led.c
 *
 * @brief This file controls LEDs.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "led.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//---------------------------------- MACROS -----------------------------------
#define GPIO_LED_BLUE 14
#define GPIO_BIT_MASK(X) ((1ULL << (X)))

//-------------------------------- DATA TYPES ---------------------------------


//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
static void _led_init(uint8_t pin)
{
    // zero-initialize the config structure.
    gpio_config_t io_conf = {};
    // disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    // set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    // bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_BIT_MASK(pin);
    // disable pull-down mode
    io_conf.pull_down_en = 0;
    // disable pull-up mode
    io_conf.pull_up_en = 0;
    // configure GPIO with the given settings
    gpio_config(&io_conf);
}

static void _led_on(uint8_t pin)
{
    gpio_set_level(pin, 1U);
}

static void _led_off(uint8_t pin)
{
    gpio_set_level(pin, 0U);
}

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void blink_blue_led(){
    _led_init(GPIO_LED_BLUE);

    for(;;)
    {
        
        _led_on(GPIO_LED_BLUE);
        vTaskDelay(800U / portTICK_PERIOD_MS);
        _led_off(GPIO_LED_BLUE);
        vTaskDelay(200U / portTICK_PERIOD_MS);
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
