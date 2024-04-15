/**
 * @file gui_app.c
 *
 * @brief This file runs the UI.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include <stdio.h>
#include "gui_app.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/* Littlevgl specific */
#include "lvgl.h"
#include "lvgl_helpers.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief This function handles events that happen on LVGL buttons.
 *
 * @param [in] p_event Pointer to the event type.
 */
static void _button_event_handler(lv_event_t *p_event);

/**
 * @brief The function unblockingly sends an event to the user interface queue.
 *
 * @param event Gui event to be sent.
 */
static void _gui_app_event_send(gui_app_event_t event);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------
extern QueueHandle_t p_user_interface_queue;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void gui_app_SC1_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Title = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Title, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Title, 2);
    lv_obj_set_y(ui_Title, -102);
    lv_obj_set_align(ui_Title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Title, "Merkur info:");

    ui_Hum = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Hum, 116);
    lv_obj_set_height(ui_Hum, 27);
    lv_obj_set_x(ui_Hum, 65);
    lv_obj_set_y(ui_Hum, -26);
    lv_obj_set_align(ui_Hum, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Hum, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Temp = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Temp, 116);
    lv_obj_set_height(ui_Temp, 27);
    lv_obj_set_x(ui_Temp, 64);
    lv_obj_set_y(ui_Temp, -61);
    lv_obj_set_align(ui_Temp, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Temp, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Acc = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Acc, 116);
    lv_obj_set_height(ui_Acc, 72);
    lv_obj_set_x(ui_Acc, 66);
    lv_obj_set_y(ui_Acc, 36);
    lv_obj_set_align(ui_Acc, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Acc, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t *ui_Button2_lab;
    ui_Button2 = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Button2, 62);
    lv_obj_set_height(ui_Button2, 23);
    lv_obj_set_x(ui_Button2, 121);
    lv_obj_set_y(ui_Button2, 101);
    lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_Button2_lab = lv_label_create(ui_Button2);
    lv_label_set_text(ui_Button2_lab, "Right");

    (void)lv_obj_add_event_cb(ui_Button2, _button_event_handler, LV_EVENT_CLICKED, NULL);

    ui_TempLabel = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_TempLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempLabel, -97);
    lv_obj_set_y(ui_TempLabel, -62);
    lv_obj_set_align(ui_TempLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempLabel, "Temperature:");

    ui_HumLab = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_HumLab, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_HumLab, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_HumLab, -85);
    lv_obj_set_y(ui_HumLab, -26);
    lv_obj_set_align(ui_HumLab, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HumLab, "Humidity:");

    ui_AccLab = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_AccLab, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AccLab, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AccLab, -98);
    lv_obj_set_y(ui_AccLab, 15);
    lv_obj_set_align(ui_AccLab, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AccLab, "Acceleration:");
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _button_event_handler(lv_event_t *p_event) 
{
    if (ui_Button2 == p_event->target)
    {
        if(LV_EVENT_CLICKED == p_event->code)
        {
            printf("Right Button clicked\n");
            _gui_app_event_send(GUI_APP_EVENT_BUTTON2_SC1_PRESSED);
        }
    }
    else
    {
        /* Unknown button event. */
    }
}

static void _gui_app_event_send(gui_app_event_t event)
{
    if(p_user_interface_queue != NULL)
    {
        xQueueSend(p_user_interface_queue, &event, 0U);
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------