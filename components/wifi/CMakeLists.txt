set(COMPONENT_SRCS "wifi.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES esp_event esp_netif esp_wifi nvs_flash)

register_component()
