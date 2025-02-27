#ifndef DEVICE_INFO
#define DEVICE_INFO

#include "esp_bt.h"
#include "esp_gap_bt_api.h"

void display_device_prop(esp_bt_gap_dev_prop_t *prop);
void decode_cod(uint32_t cod);
// void example_usage(esp_bt_gap_dev_prop_t *dev_prop, int num_prop);

#endif // DEVICE_INFO