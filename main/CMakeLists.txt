idf_component_register(SRCS "client_start.c" "host_start.c" "main.c"
                    INCLUDE_DIRS ""
                    REQUIRES uartFunction game)

spiffs_create_partition_image(storage ../tools FLASH_IN_PROJECT)