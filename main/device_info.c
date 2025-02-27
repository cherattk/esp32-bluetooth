#include "device_info.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

static const char *REMOTE_DEV_PROP = "REMOTE_DEVICE_PROPERTIE";

void display_device_prop(esp_bt_gap_dev_prop_t *prop) {
    if (prop == NULL) {
        ESP_LOGE(REMOTE_DEV_PROP, "is NULL");
        return;
    }

    switch (prop->type) {
        case ESP_BT_GAP_DEV_PROP_BDNAME:
            ESP_LOGI(REMOTE_DEV_PROP, "Device Name: %.*s", prop->len, (char *)prop->val);
            break;
        case ESP_BT_GAP_DEV_PROP_RSSI:
            ESP_LOGI(REMOTE_DEV_PROP, "RSSI: %d", *((int8_t *)prop->val));
            break;
        case ESP_BT_GAP_DEV_PROP_COD:
            //ESP_LOGI(REMOTE_DEV_PROP, "Class of Device CoD: %lu", *((uint32_t *)prop->val));
            decode_cod(*((uint32_t *)prop->val));
            break;
        case ESP_BT_GAP_DEV_PROP_EIR:
            ESP_LOGI(REMOTE_DEV_PROP, "EIR: %.*s", prop->len, (char *)prop->val);
           
            break;
        // case ESP_BT_GAP_DEV_PROP_BDADDR:
        //     ESP_LOGI(TAG, "BD Address: %02x:%02x:%02x:%02x:%02x:%02x",
        //              ((uint8_t *)prop->val)[0], ((uint8_t *)prop->val)[1],
        //              ((uint8_t *)prop->val)[2], ((uint8_t *)prop->val)[3],
        //              ((uint8_t *)prop->val)[4], ((uint8_t *)prop->val)[5]);
        //     break;
        // Add cases for other property types as needed
        default:
            ESP_LOGI(REMOTE_DEV_PROP, "Unknown property type: %d", prop->type);
            break;
    }
}

void decode_cod(uint32_t cod) {
    uint32_t service_class = (cod >> 13) & 0x07FF;
    uint32_t major_device_class = (cod >> 8) & 0x1F;
    uint32_t minor_device_class = (cod >> 2) & 0x3F;

    ESP_LOGI(REMOTE_DEV_PROP,"  Class of Device: 0x%06X", (unsigned int)cod);
    ESP_LOGI(REMOTE_DEV_PROP,"  Service Class: 0x%04X", (unsigned int)service_class);
    ESP_LOGI(REMOTE_DEV_PROP,"  Major Device Class: 0x%02X", (unsigned int)major_device_class);
    ESP_LOGI(REMOTE_DEV_PROP,"  Minor Device Class: 0x%02X", (unsigned int)minor_device_class);

    // Add logic to interpret the classes (see below)
}