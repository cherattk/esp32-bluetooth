/**
 * ESP32 BT Classic
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"

#include "time.h"
#include "sys/time.h"

#define DEVICE_NAME "ESP32_SPP_SERVER"
#define MAIN_TAG "MAIN_APP"
#define SPP_TAG "SPP_CALLBACK"
#define GAP_TAG "GAP_CALLBACK"

static const esp_spp_sec_t spp_sec_mask = ESP_SPP_SEC_NONE;
static const esp_spp_role_t spp_role = ESP_SPP_ROLE_SLAVE;

static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    switch (event)
    {
    case ESP_SPP_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
        esp_spp_start_srv(spp_sec_mask, spp_role, 0, DEVICE_NAME);
        break;

    case ESP_SPP_DISCOVERY_COMP_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT");
        break;

    case ESP_SPP_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_OPEN_EVT");
        break;

    case ESP_SPP_CLOSE_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CLOSE_EVT");
        break;

    case ESP_SPP_START_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_START_EVT");
        break;

    case ESP_SPP_CL_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
        break;

    case ESP_SPP_DATA_IND_EVT:
        // receive param->data_ind
        ESP_LOGI(SPP_TAG, "ESP_SPP_DATA_IND_EVT");
        break;

    case ESP_SPP_CONG_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CONG_EVT");
        break;

    case ESP_SPP_WRITE_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_WRITE_EVT");
        break;

    case ESP_SPP_SRV_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT");
        break;

    case ESP_SPP_SRV_STOP_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_STOP_EVT");
        break;

    case ESP_SPP_UNINIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_UNINIT_EVT");
        break;

    default:
        ESP_LOGI(SPP_TAG, "Unhandled event : %d" , (unsigned int) event);
        break;
    }
}

void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event)
    {
    case ESP_BT_GAP_AUTH_CMPL_EVT:
    {
        ESP_LOGI(GAP_TAG, "ESP_BT_GAP_AUTH_CMPL_EVT");
        break;
    }
    case ESP_BT_GAP_PIN_REQ_EVT:
    {
        ESP_LOGI(GAP_TAG, "ESP_BT_GAP_PIN_REQ_EVT");
        break;
    }
    case ESP_BT_GAP_MODE_CHG_EVT:
        ESP_LOGI(GAP_TAG, "ESP_BT_GAP_MODE_CHG_EVT");
        break;

    default:
    {
        ESP_LOGI(GAP_TAG, "Unhandled event : %d" , (unsigned int) event);
        break;
    }
    }
    return;
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s initialize controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
    // true => use SSP (secure simple pairing)
    // false => use legacy pairing with pin code set with esp_bt_gap_set_pin()
    // default => true
    // bluedroid_cfg.ssp_en = false;

    if ((ret = esp_bluedroid_init_with_cfg(&bluedroid_cfg)) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s initialize bluedroid failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s enable bluedroid failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_gap_register_callback(esp_bt_gap_cb)) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s gap callback register failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_register_callback(esp_spp_cb)) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s spp callback register failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    esp_spp_cfg_t spp_cfg = BT_SPP_DEFAULT_CONFIG();
    spp_cfg.mode = ESP_SPP_MODE_CB;
    spp_cfg.enable_l2cap_ertm = true;

    if ((ret = esp_spp_enhanced_init(&spp_cfg)) != ESP_OK)
    {
        ESP_LOGE(MAIN_TAG, "%s spp init failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    esp_bt_dev_set_device_name(DEVICE_NAME);
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

}
