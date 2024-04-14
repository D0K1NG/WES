#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include <stdbool.h>

// Initialize MQTT publisher
bool mqtt_init(const char* broker_address, int port, const char* client_id);

// Publish JSON formatted data
bool mqtt_publish_data(float temperature, float humidity, float acc_x, float acc_y, float acc_z);

// Disconnect MQTT client
void mqtt_disconnect();

#endif // MQTT_PUBLISHER_H
