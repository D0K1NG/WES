/**
 * @file main.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "user_interface.h"
#include "wifi.h"
#include "led.h"
#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    xTaskCreate(&blink_blue_led, "BlinkBlueLedTask", 2 * 1024, NULL, 5, NULL);
    xTaskCreate(&morse_SOS_buzzer, "MorseSosBuzzerTask", 4 * 1024, NULL, 5, NULL);

    //setupWifi();
    
    user_interface_init();
    
    
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
