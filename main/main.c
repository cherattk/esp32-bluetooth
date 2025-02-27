#include "device_info.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
// #include "nvs.h"
#include "nvs_flash.h"
#include "esp_spp_api.h"
#include "device_info.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_log.h"

#define SPP_TAG "SPP_CLIENT"
#define SPP_SERVER_NAME "ESP32_SPP_SERVER"
// static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;

static void esp_spp_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    switch (event) {
        case ESP_SPP_INIT_EVT:
            ESP_LOGI(SPP_TAG, "SPP initialized ...");
            break;
        case ESP_SPP_OPEN_EVT:
            ESP_LOGI(SPP_TAG, "SPP connection opened, sending data...");
            esp_spp_write(param->open.handle, strlen("Hello ESP32 Server"), (uint8_t *)"Hello ESP32 Server");
            break;
        case ESP_SPP_CLOSE_EVT:
            ESP_LOGI(SPP_TAG, "SPP connection closed");
            break;
        case ESP_SPP_DATA_IND_EVT:
            ESP_LOGI(SPP_TAG, "Received data: %.*s", param->data_ind.len, param->data_ind.data);
            break;
        default:
            ESP_LOGI(SPP_TAG, "Nothing happened");
            break;
    }
}

static void esp_bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
    switch (event) {
        case ESP_BT_GAP_DISC_RES_EVT:
            ESP_LOGI(SPP_TAG, "Device found, processing...");
            
            int number_prop = param->disc_res.num_prop;
            esp_bt_gap_dev_prop_t *device_prop = param->disc_res.prop;
            for(int i = 0; i < number_prop; i++){
                display_device_prop(&device_prop[i]);
            }
            break;

        // case ESP_BT_GAP_READ_REMOTE_NAME_EVT:
        //     if (param->read_remote_name.stat == ESP_BT_STATUS_SUCCESS) {
        //         ESP_LOGI(TAG, "Remote device name: %s", param->read_remote_name.remote_name);
        //     } else {
        //         ESP_LOGE(TAG, "Failed to read remote device name");
        //     }
        //     break;

        case ESP_BT_GAP_DISC_STATE_CHANGED_EVT:
            if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STOPPED) {
                ESP_LOGI(SPP_TAG, "Device discovery stopped");
            }
            break;
        default:
            break;
    }
}

void app_main() {
    esp_err_t ret;

    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret != ESP_OK) {
        //ESP_LOGE(SPP_TAG, "BT Controller initialization failed");
        ESP_LOGE(SPP_TAG, "%s initialize controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }
    // ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
    if (ret != ESP_OK) {
        //ESP_LOGE(SPP_TAG, "BT Controller enable failed");
        ESP_LOGE(SPP_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    // bluedroid
    esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
    ret = esp_bluedroid_init_with_cfg(&bluedroid_cfg);
    if (ret != ESP_OK) {
        //ESP_LOGE(SPP_TAG, "Bluedroid initialization failed");
        ESP_LOGE(SPP_TAG, "%s initialize bluedroid failed: %s", __func__, esp_err_to_name(ret));
        return;
    }
    
    ret = esp_bluedroid_enable();
    if (ret != ESP_OK) {
        //ESP_LOGE(SPP_TAG, "Bluedroid enable failed");
        ESP_LOGE(SPP_TAG, "%s enable bluedroid failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_gap_register_callback(esp_bt_gap_callback);
    if (ret != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s gap register failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    esp_spp_cfg_t spp_cfg = BT_SPP_DEFAULT_CONFIG();
    spp_cfg.mode = ESP_SPP_MODE_CB;
    // must be called after esp_bluedroid_enable()
    ret = esp_spp_enhanced_init(&spp_cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp init failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_spp_register_callback(esp_spp_callback);
    if (ret != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp register failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
    if(ret != ESP_OK){
        ESP_LOGE(SPP_TAG, "Set scan mode failed");
        return;
    }

    // Start discovery
    ret = esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0); // 10 seconds timeout
    if (ret != ESP_OK) {
        ESP_LOGE(SPP_TAG, "Discovery start failed");
        return;
    }
    else{
        ESP_LOGI(SPP_TAG, "starting discovery...");
    }

    ESP_LOGI(SPP_TAG, "all initializations successfully done");
    
}
