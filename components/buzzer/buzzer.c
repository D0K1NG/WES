/**
 * @file buzzer.c
 *
 * @brief This file controls the buzzer.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "esp_system.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#include "sdkconfig.h"

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

#define BUZZ_GPIO_OUTPUT    2U
//#define GPIO_OUTPUT_SPEED LEDC_LOW_SPEED_MODE // back too old git commit :-(
#define GPIO_OUTPUT_SPEED LEDC_HIGH_SPEED_MODE

void sound(int freq, int duration) {


	ledc_timer_config_t timer_conf;
	timer_conf.speed_mode = GPIO_OUTPUT_SPEED;  
	timer_conf.duty_resolution    = LEDC_TIMER_10_BIT;
	timer_conf.timer_num  = LEDC_TIMER_0;
	timer_conf.freq_hz    = freq;
	ledc_timer_config(&timer_conf);

	ledc_channel_config_t ledc_conf;
	ledc_conf.gpio_num   = BUZZ_GPIO_OUTPUT;
	ledc_conf.speed_mode = GPIO_OUTPUT_SPEED;
	ledc_conf.channel    = LEDC_CHANNEL_0;
	ledc_conf.intr_type  = LEDC_INTR_DISABLE;
	ledc_conf.timer_sel  = LEDC_TIMER_0;
	ledc_conf.duty       = 0x7FFF; // 50%=0x3FFF, 100%=0x7FFF for 15 Bit
	                            // 50%=0x01FF, 100%=0x03FF for 10 Bit
	ledc_channel_config(&ledc_conf);

	// start
    ledc_set_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0, 0x7FFF); // 100% duty - play here for your speaker or buzzer
    ledc_update_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0);
	vTaskDelay(duration/portTICK_PERIOD_MS);
	// stop
    ledc_set_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0, 0);
    ledc_update_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0);
    

}

void morse_SOS_buzzer(){
    sound(a, 1000);
    vTaskDelay(1000U/portTICK_PERIOD_MS);
    sound(a, 1000);
    vTaskDelay(1000U/portTICK_PERIOD_MS);
    sound(a, 1000);
    vTaskDelay(3000U/portTICK_PERIOD_MS);

    sound(a, 3000);
    vTaskDelay(1000U/portTICK_PERIOD_MS);
    sound(a, 3000);
    vTaskDelay(1000U/portTICK_PERIOD_MS);
    sound(a, 3000);
    vTaskDelay(3000U/portTICK_PERIOD_MS);

    sound(a, 1000);
    vTaskDelay(1000U/portTICK_PERIOD_MS);
    sound(a, 1000);
    vTaskDelay(1000U/portTICK_PERIOD_MS);
    sound(a, 1000);
    
}