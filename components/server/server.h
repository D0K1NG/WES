#include "mqtt_client.h"
#include "../json/cJSON/cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"

typedef struct {
    int temp;
    float hum;
    float acc_x;
    float acc_y;
    float acc_z;
} SensorData;

void publish_sensor_data(esp_mqtt_client_handle_t client, SensorData *data);
void some_function();
esp_event_handler_t kurac(esp_mqtt_client_handle_t client, SensorData *data);

