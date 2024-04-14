#include "mqtt_client.h"
#include "mqtt-pn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOPIC "WES/Mercury/sensors"

static MQTTClient client;
static MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
static char json_buffer[256]; // JSON buffer size

// Callback function for connection lost
static void connection_lost(void* context, char* cause) {
    printf("\nConnection lost\n");
}

// Callback function for message delivered
static void delivery_complete(void* context, MQTTClient_deliveryToken token) {
    printf("Message delivered\n");
}

// Initialize MQTT publisher
bool mqtt_init(const char* broker_address, int port, const char* client_id) {
    MQTTClient_create(&client, broker_address, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, NULL, connection_lost, delivery_complete, NULL);

    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to MQTT broker\n");
        return false;
    }

    printf("Connected to MQTT broker\n");
    return true;
}

// Publish JSON formatted data
bool mqtt_publish_data(float temperature, float humidity, float acc_x, float acc_y, float acc_z) {
    snprintf(json_buffer, sizeof(json_buffer),
             "{\"temp\": %.2f, \"hum\": %.2f, \"acc\": {\"x\": %.2f, \"y\": %.2f, \"z\": %.2f}}",
             temperature, humidity, acc_x, acc_y, acc_z);

    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = json_buffer;
    pubmsg.payloadlen = (int)strlen(json_buffer);
    pubmsg.qos = 1;
    pubmsg.retained = 0;

    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, 1000);

    return true;
}

// Disconnect MQTT client
void mqtt_disconnect() {
    MQTTClient_disconnect(client, 1000);
    MQTTClient_destroy(&client);
}
