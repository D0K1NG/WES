/**
 * @file led.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __LED_C__
#define __LED_C__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "esp_err.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
void blink_blue_led();

#ifdef __cplusplus
}
#endif

#endif // __LED_C__
