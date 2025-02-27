idf_component_register(SRCS "main.c" "device_info.c"
                    REQUIRES bt nvs_flash
                    INCLUDE_DIRS ".")
