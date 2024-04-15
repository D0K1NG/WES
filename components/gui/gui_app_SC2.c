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
void gui_app_SC2_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Title2 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Title2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Title2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Title2, 2);
    lv_obj_set_y(ui_Title2, -102);
    lv_obj_set_align(ui_Title2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Title2, "Igrica:");

    ui_Temp1 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Temp1, 116);
    lv_obj_set_height(ui_Temp1, 27);
    lv_obj_set_x(ui_Temp1, 64);
    lv_obj_set_y(ui_Temp1, -61);
    lv_obj_set_align(ui_Temp1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Temp1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t *ui_Button3_lab;
    ui_Button3 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button3, 64);
    lv_obj_set_height(ui_Button3, 23);
    lv_obj_set_x(ui_Button3, -118);
    lv_obj_set_y(ui_Button3, 100);
    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_Button3_lab = lv_label_create(ui_Button3);
    lv_label_set_text(ui_Button3_lab, "Left");

    (void)lv_obj_add_event_cb(ui_Button3, _button_event_handler, LV_EVENT_CLICKED, NULL);

    ui_Scr2Lab = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Scr2Lab, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Scr2Lab, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Scr2Lab, -97);
    lv_obj_set_y(ui_Scr2Lab, -62);
    lv_obj_set_align(ui_Scr2Lab, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Scr2Lab, "Igrica");
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _button_event_handler(lv_event_t *p_event) 
{
    if(ui_Button3 == p_event->target)
    {
        if(LV_EVENT_CLICKED == p_event->code)
        {
            printf("Left Button clicked\n");
            _gui_app_event_send(GUI_APP_EVENT_BUTTON3_SC2_PRESSED);
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