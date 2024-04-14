#include "mqtt_client.h"
#include "server.h"
#include "../json/cJSON/cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"

void publish_sensor_data(esp_mqtt_client_handle_t client, SensorData *data) {
    // Create a JSON object
    cJSON *json = cJSON_CreateObject();

    // Add temperature and humidity to the JSON object
    cJSON_AddNumberToObject(json, "temp", data->temp);
    cJSON_AddNumberToObject(json, "hum", data->hum);

    // Create a JSON object for acceleration data
    cJSON *acc_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(acc_json, "x", data->acc_x);
    cJSON_AddNumberToObject(acc_json, "y", data->acc_y);
    cJSON_AddNumberToObject(acc_json, "z", data->acc_z);

    // Add the acceleration object to the main JSON object
    cJSON_AddItemToObject(json, "acc", acc_json);

    // Convert the JSON object to a string
    char *json_string = cJSON_Print(json);

    // Publish the JSON string to the topic
    esp_mqtt_client_publish(client, "WES/Planet/sensors", json_string, 0, 1, 0);

    // Clean up
    cJSON_Delete(json);
    free(json_string);
}


void kurac()
{

}
void some_function() {
    printf("esagluk: in some_function\n");
    // Initialize your MQTT client as before...

    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://192.168.254.6",
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    printf("esagluk: b4 kurac\n");
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, kurac, client);
    printf("esagluk: after kurac\n");
    esp_mqtt_client_start(client);

    // Create some sensor data
    SensorData data = { .temp = 25,  .hum = 0.55, .acc_x = 0.11, .acc_y = 0.11, .acc_z = 0.11};

    // Publish the sensor data
    printf("esagluk: b4 publish\n");
    publish_sensor_data(client, &data);
}

    int temp;
    float hum;
    float acc_x;
    float acc_y;
    float acc_z;