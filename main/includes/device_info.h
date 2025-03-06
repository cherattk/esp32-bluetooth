/**
 * 
 */


#ifndef __DEVICE_INFO__
#define __DEVICE_INFO__

#include "esp_gap_bt_api.h"

void log_device_prop(esp_bt_gap_dev_prop_t *prop);
void decode_class_device(uint32_t cod ,  
                        unsigned int *service_class ,  
                        unsigned int *major_device_class ,  
                        unsigned int *minor_device_class);

#endif // __DEVICE_INFO__