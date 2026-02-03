/**
Connect ESP32-S3 to ESP-NN
   Filename:      userwords.h
   Date:          03 feb 2026
   Updated:       03 feb 2026
   File Version:  1.0
   MCU:           ESP32-S3 WROOM only !!
   Forth:         ESP32forth all versions 7.0.7.21c+
   Copyright:     Marc PETREMANN
   Author:        Marc PETREMANN
   GNU General Public License
*/



#include "esp_nn_wrapper.h"

#define USER_WORDS \
X("nn.dot_product_s8", NN_DOT_S8, \
    int32_t res = 0; \
    esp_nn_dot_product_s8((int8_t*)n3, (int8_t*)n2, (int16_t)n1, (int16_t)n0, &res); \
    DROPn(3); n0 = res) \
X("nn.dot_product_s16", NN_DOT_S16, \
    int32_t res = 0; \
    esp_nn_dot_product_s16((int16_t*)n3, (int16_t*)n2, (int16_t)n1, (int16_t)n0, &res); \
    DROPn(3); n0 = res) \
X("nn.relu_s8", NN_RELU_S8, \
    esp_nn_relu_s8((int8_t*)n1, (int32_t)n0); \
    DROPn(2)) \
X("nn.relu_s16", NN_RELU_S16, \
    esp_nn_relu_s16((int16_t*)n1, (uint16_t)n0); \
    DROPn(2)) \
X("nn.relu6_s8", NN_RELU6_S8, \
    esp_nn_relu6_s8((int8_t*)n1, (int32_t)n0); \
    DROPn(2)) \
X("nn.add_s8", NN_ADD_S8, \
    esp_nn_add_elementwise_s8((int8_t*)n3, (int8_t*)n2, (int8_t*)n1, (int32_t)n0); \
    DROPn(4)) \
X("nn.mul_s8", NN_MUL_S8, \
    esp_nn_mul_elementwise_s8((int8_t*)n3, (int8_t*)n2, (int8_t*)n1, (int32_t)n0); \
    DROPn(4)) \
X("nn.max_pool_s8", NN_MAXPOOL_S8, \
    esp_nn_max_pool_s8((int8_t*)n4, (int8_t*)n3, (int16_t)n2, (int16_t)n1, (int16_t)n0); \
    DROPn(5)) \
X("nn.avg_pool_s8", NN_AVGPOOL_S8, \
    esp_nn_avg_pool_s8((int8_t*)n4, (int8_t*)n3, (int16_t)n2, (int16_t)n1, (int16_t)n0); \
    DROPn(5)) \
X("nn.conv_s8", NN_CONV_S8, \
    esp_nn_conv_s8_simple((int8_t*)n6, (int8_t*)n5, (int8_t*)n4, (int16_t)n3, (int16_t)n2, (int16_t)n1, (int16_t)n0); \
    DROPn(7)) \
X("nn.fc_s8", NN_FC_S8, \
    esp_nn_fully_connected_s8((int8_t*)n4, (int8_t*)n3, (int8_t*)n2, (int16_t)n1, (int16_t)n0); \
    DROPn(5)) \
X("nn.set_s8", NN_SET_S8, \
    esp_nn_set_element_s8((int8_t*)n3, (int32_t)n2, (int32_t)n1, (int8_t)n0); \
    DROPn(4)) \
X("nn.get_s8", NN_GET_S8, \
    DROPn(1); n0 = esp_nn_get_element_s8((int8_t*)n1, (int32_t)n0)) \
X("nn.set_s16", NN_SET_S16, \
    esp_nn_set_element_s16((int16_t*)n3, (int32_t)n2, (int32_t)n1, (int16_t)n0); \
    DROPn(4)) \
X("nn.get_s16", NN_GET_S16, \
    DROPn(1); n0 = esp_nn_get_element_s16((int16_t*)n1, (int32_t)n0))

