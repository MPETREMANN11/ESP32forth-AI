/**
Connect ESP32-S3 to ESP-NN
   Filename:      userwords.h
   Date:          22 feb 2026
   Updated:       22 feb 2026
   File Version:  1.0
   MCU:           ESP32-S3 WROOM only !!
   Forth:         ESP32forth all versions 7.0.7.21c+
   Copyright:     Marc PETREMANN
   Author:        Marc PETREMANN
   GNU General Public License
*/

// link: https://github.com/espressif/esp-nn

extern "C" {
  #include "esp_nn.h"
}

#define USER_WORDS \
/** nn.add_elementwise_s8 ( ..16elements.. -- ) */ \
X("nn.add_elementwise_s8", NN_ADD_S8, \
    esp_nn_add_elementwise_s8( \
        (const int8_t*)n15,     /* input1_data */ \
        (const int8_t*)n14,     /* input2_data */ \
        (int32_t)n13,           /* input 1 offset */ \
        (int32_t)n12,           /* input 2 offset */ \
        (int32_t)n11,           /* input 1 multiplier */ \
        (int32_t)n10,           /* input 2 multiplier */ \
        (int32_t)n9,            /* input 1 shift */ \
        (int32_t)n8,            /* input 2 shift */ \
        (int32_t)n7,            /* left_shift */ \
        (int8_t*)n6,            /* output pointer */ \
        (int32_t)n5,            /* out_offset */ \
        (int32_t)n4,            /* out_mult */ \
        (int32_t)n3,            /* out_shift */ \
        (int32_t)n2,            /* activation min */ \
        (int32_t)n1,            /* activation max */ \
        (int32_t)n0             /* size */ \
    ); DROPn(16)) \
/** nn.mul_elementwise_s8 ( ..11elements.. -- ) */ \
X("nn.mul_elementwise_s8", NN_MUL_S8, \
    esp_nn_mul_elementwise_s8( \
        (const int8_t*)n10,     /* input1_data */ \
        (const int8_t*)n9,     /* input2_data */ \
        (int32_t)n8,            /* input 1 offset */ \
        (int32_t)n7,            /* input 2 offset */ \
        (int8_t*)n6,            /* output pointer */ \
        (int32_t)n5,            /* out_offset */ \
        (int32_t)n4,            /* out_mult */ \
        (int32_t)n3,            /* out_shift */ \
        (int32_t)n2,            /* activation min */ \
        (int32_t)n1,            /* activation max */ \
        (int32_t)n0             /* size */ \
    ); DROPn(11)) \
/** nn.set_element_s8 ( array index size value -- ) */ \
X("nn.set_element_s8", NN_SET_S8, \
    { \
        int8_t *arr = (int8_t*)n3; \
        int32_t idx = (int32_t)n2; \
        int32_t sz  = (int32_t)n1; \
        int8_t  val = (int8_t)n0;  \
        if (idx >= 0 && idx < sz) { \
            arr[idx] = val; \
        } \
    } \
    DROPn(4)) \
/** nn.get_element_s8 ( array index -- value ) */ \
X("nn.get_element_s8", NN_GET_S8, \
    { \
        const int8_t *arr = (const int8_t*)n1; \
        int32_t idx = (int32_t)n0; \
        n1 = (int32_t)arr[idx]; \
    } \
    DROPn(1)) \
/** nn.set_element_s16 ( array index size value -- ) */ \
X("nn.set_element_s16", NN_SET_S16, \
    { \
        int16_t *arr = (int16_t*)n3; \
        int32_t idx = (int32_t)n2; \
        int32_t sz  = (int32_t)n1; \
        int16_t val = (int16_t)n0; \
        if (idx >= 0 && idx < sz) { \
            arr[idx] = val; \
        } \
    } \
    DROPn(4)) \
/** nn.get_element_s16 ( array index -- value ) */ \
X("nn.get_element_s16", NN_GET_S16, \
    { \
        const int16_t *arr = (const int16_t*)n1; \
        int32_t idx = (int32_t)n0; \
        n1 = (int32_t)arr[idx]; \
    } \
    DROPn(1))

