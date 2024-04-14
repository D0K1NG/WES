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
<<<<<<< Updated upstream
#include "../components/wifi/wifi.h"
#include "../components/mqtt-PN/mqtt-pn.h"
=======
#include "wifi.h"
#include "led.h"
>>>>>>> Stashed changes

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    setupWifi();
    user_interface_init();
    
<<<<<<< Updated upstream
=======
    led_init();
    
>>>>>>> Stashed changes
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
