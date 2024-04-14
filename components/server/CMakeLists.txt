set(COMPONENT_SRCS "server.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES driver esp_event esp_netif mqtt)

register_component()
