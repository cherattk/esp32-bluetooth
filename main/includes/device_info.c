/**
 * 
 */

#include <stdio.h>
#include <string.h>
#include "esp_bt.h"
#include "esp_spp_api.h"
#include "esp_log.h"

#include "device_info.h"

#define DEVICE_PROP "DEVICE_PROP"

void log_device_prop(esp_bt_gap_dev_prop_t *prop) {
    if (prop == NULL) {
        ESP_LOGE(DEVICE_PROP, "is NULL");
        return;
    }

    switch (prop->type) {
        case ESP_BT_GAP_DEV_PROP_BDNAME:
            ESP_LOGI(DEVICE_PROP, "Device Name: %.*s", prop->len, (char *)prop->val);
            break;
        case ESP_BT_GAP_DEV_PROP_RSSI:
            ESP_LOGI(DEVICE_PROP, "RSSI: %d", *((int8_t *)prop->val));
            break;
        case ESP_BT_GAP_DEV_PROP_COD:

            unsigned int service_class = 0;
            unsigned int maj_dev_class = 0;
            unsigned int min_dev_class = 0;

            decode_class_device(*((uint32_t *)prop->val) , &service_class , &maj_dev_class , &min_dev_class);
            // 
            ESP_LOGI(DEVICE_PROP,"  Class of Device: 0x%06X", *((unsigned int *)prop->val));
            ESP_LOGI(DEVICE_PROP,"  Service Class: 0x%04X", service_class);
            ESP_LOGI(DEVICE_PROP,"  Major Device Class: 0x%02X", maj_dev_class);
            ESP_LOGI(DEVICE_PROP,"  Minor Device Class: 0x%02X", min_dev_class);
        break;

        case ESP_BT_GAP_DEV_PROP_EIR:
            ESP_LOGI(DEVICE_PROP, "EIR: %.*s \n", prop->len, (char *)prop->val);
           
        break;
        // case ESP_BT_GAP_DEV_PROP_BDADDR:
        //     ESP_LOGI(TAG, "BD Address: %02x:%02x:%02x:%02x:%02x:%02x",
        //              ((uint8_t *)prop->val)[0], ((uint8_t *)prop->val)[1],
        //              ((uint8_t *)prop->val)[2], ((uint8_t *)prop->val)[3],
        //              ((uint8_t *)prop->val)[4], ((uint8_t *)prop->val)[5]);
        //     break;
        default:
            ESP_LOGI(DEVICE_PROP, "Unknown property type: %d", prop->type);
            break;
    }
}

void decode_class_device(uint32_t cod ,  
    unsigned int *service_class ,  
    unsigned int *major_device_class ,  
    unsigned int *minor_device_class) {
    //
    *service_class = (cod >> 13) & 0x07FF;
    *major_device_class = (cod >> 8) & 0x1F;
    *minor_device_class = (cod >> 2) & 0x3F;
}
