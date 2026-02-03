
#ifndef ESP_NN_WRAPPER_H
#define ESP_NN_WRAPPER_H

#include <stdint.h>

// ============================================================================
// OPÉRATIONS ÉLÉMENTAIRES (Element-wise)
// ============================================================================

// Addition élément par élément (int8)
inline void esp_nn_add_elementwise_s8(const int8_t *input1, const int8_t *input2, 
                                       int8_t *output, int32_t size) {
    for(int32_t i = 0; i < size; i++) {
        int32_t sum = (int32_t)input1[i] + (int32_t)input2[i];
        // Clamping pour éviter overflow
        output[i] = (sum > 127) ? 127 : (sum < -128) ? -128 : (int8_t)sum;
    }
}

// Multiplication élément par élément (int8)
inline void esp_nn_mul_elementwise_s8(const int8_t *input1, const int8_t *input2,
                                       int8_t *output, int32_t size) {
    for(int32_t i = 0; i < size; i++) {
        int32_t prod = ((int32_t)input1[i] * (int32_t)input2[i]) >> 7; // Division par 128
        output[i] = (prod > 127) ? 127 : (prod < -128) ? -128 : (int8_t)prod;
    }
}

// ============================================================================
// PRODUITS SCALAIRES (Dot Product)
// ============================================================================

// Produit scalaire int8
inline void esp_nn_dot_product_s8(const int8_t *vec1, const int8_t *vec2, 
                                   int16_t len, int16_t offset, int32_t *out) {
    int32_t sum = 0;
    for(int16_t i = 0; i < len; i++) {
        sum += (int32_t)vec1[i + offset] * (int32_t)vec2[i];
    }
    *out = sum;
}

// Produit scalaire int16
inline void esp_nn_dot_product_s16(const int16_t *vec1, const int16_t *vec2,
                                    int16_t len, int16_t offset, int32_t *out) {
    int32_t sum = 0;
    for(int16_t i = 0; i < len; i++) {
        sum += (int32_t)vec1[i + offset] * (int32_t)vec2[i];
    }
    *out = sum;
}

// ============================================================================
// FONCTIONS D'ACTIVATION
// ============================================================================

// ReLU pour int8
inline void esp_nn_relu_s8(int8_t *data, int32_t size) {
    for(int32_t i = 0; i < size; i++) {
        if(data[i] < 0) data[i] = 0;
    }
}

// ReLU pour int16
inline void esp_nn_relu_s16(int16_t *data, uint16_t size) {
    for(uint16_t i = 0; i < size; i++) {
        if(data[i] < 0) data[i] = 0;
    }
}

// ReLU6 pour int8 (clamp entre 0 et 6)
inline void esp_nn_relu6_s8(int8_t *data, int32_t size) {
    for(int32_t i = 0; i < size; i++) {
        if(data[i] < 0) data[i] = 0;
        else if(data[i] > 6) data[i] = 6;
    }
}

// ============================================================================
// POOLING
// ============================================================================

// Max pooling 2D (simplifié - fenêtre 2x2, stride 2)
inline void esp_nn_max_pool_s8(const int8_t *input, int8_t *output,
                                int16_t input_h, int16_t input_w, int16_t channels) {
    int16_t out_h = input_h / 2;
    int16_t out_w = input_w / 2;
    
    for(int16_t c = 0; c < channels; c++) {
        for(int16_t h = 0; h < out_h; h++) {
            for(int16_t w = 0; w < out_w; w++) {
                int16_t in_h = h * 2;
                int16_t in_w = w * 2;
                
                int8_t max_val = input[(in_h * input_w + in_w) * channels + c];
                int8_t val;
                
                val = input[(in_h * input_w + (in_w + 1)) * channels + c];
                if(val > max_val) max_val = val;
                
                val = input[((in_h + 1) * input_w + in_w) * channels + c];
                if(val > max_val) max_val = val;
                
                val = input[((in_h + 1) * input_w + (in_w + 1)) * channels + c];
                if(val > max_val) max_val = val;
                
                output[(h * out_w + w) * channels + c] = max_val;
            }
        }
    }
}

// Average pooling 2D (simplifié - fenêtre 2x2, stride 2)
inline void esp_nn_avg_pool_s8(const int8_t *input, int8_t *output,
                                int16_t input_h, int16_t input_w, int16_t channels) {
    int16_t out_h = input_h / 2;
    int16_t out_w = input_w / 2;
    
    for(int16_t c = 0; c < channels; c++) {
        for(int16_t h = 0; h < out_h; h++) {
            for(int16_t w = 0; w < out_w; w++) {
                int16_t in_h = h * 2;
                int16_t in_w = w * 2;
                
                int32_t sum = 0;
                sum += input[(in_h * input_w + in_w) * channels + c];
                sum += input[(in_h * input_w + (in_w + 1)) * channels + c];
                sum += input[((in_h + 1) * input_w + in_w) * channels + c];
                sum += input[((in_h + 1) * input_w + (in_w + 1)) * channels + c];
                
                output[(h * out_w + w) * channels + c] = (int8_t)(sum / 4);
            }
        }
    }
}

// ============================================================================
// CONVOLUTION
// ============================================================================

// Convolution 2D simplifiée (3x3, stride 1, no padding)
inline void esp_nn_conv_s8_simple(const int8_t *input, const int8_t *filter,
                                   int8_t *output, int16_t input_h, int16_t input_w,
                                   int16_t in_channels, int16_t out_channels) {
    const int16_t kernel_size = 3;
    int16_t out_h = input_h - kernel_size + 1;
    int16_t out_w = input_w - kernel_size + 1;
    
    for(int16_t oc = 0; oc < out_channels; oc++) {
        for(int16_t h = 0; h < out_h; h++) {
            for(int16_t w = 0; w < out_w; w++) {
                int32_t sum = 0;
                
                // Parcourir le filtre 3x3
                for(int16_t kh = 0; kh < kernel_size; kh++) {
                    for(int16_t kw = 0; kw < kernel_size; kw++) {
                        for(int16_t ic = 0; ic < in_channels; ic++) {
                            int16_t in_h = h + kh;
                            int16_t in_w = w + kw;
                            
                            int8_t in_val = input[(in_h * input_w + in_w) * in_channels + ic];
                            int8_t filt_val = filter[((oc * kernel_size + kh) * kernel_size + kw) * in_channels + ic];
                            
                            sum += (int32_t)in_val * (int32_t)filt_val;
                        }
                    }
                }
                
                // Quantification et clamping
                sum = sum >> 7; // Division par 128
                output[(h * out_w + w) * out_channels + oc] = 
                    (sum > 127) ? 127 : (sum < -128) ? -128 : (int8_t)sum;
            }
        }
    }
}

// ============================================================================
// FULLY CONNECTED
// ============================================================================

// Couche entièrement connectée
inline void esp_nn_fully_connected_s8(const int8_t *input, const int8_t *weights,
                                      int8_t *output, int16_t input_size,
                                      int16_t output_size) {
    for(int16_t i = 0; i < output_size; i++) {
        int32_t sum = 0;
        for(int16_t j = 0; j < input_size; j++) {
            sum += (int32_t)input[j] * (int32_t)weights[i * input_size + j];
        }
        sum = sum >> 7; // Division par 128
        output[i] = (sum > 127) ? 127 : (sum < -128) ? -128 : (int8_t)sum;
    }
}

// ============================================================================
// UTILITAIRES
// ============================================================================

// Définir un élément dans un tableau int8
inline void esp_nn_set_element_s8(int8_t *array, int32_t index, 
                                   int32_t size, int8_t value) {
    if(index >= 0 && index < size) {
        array[index] = value;
    }
}

// Obtenir un élément d'un tableau int8
inline int8_t esp_nn_get_element_s8(const int8_t *array, int32_t index) {
    return array[index];
}

// Définir un élément dans un tableau int16
inline void esp_nn_set_element_s16(int16_t *array, int32_t index,
                                    int32_t size, int16_t value) {
    if(index >= 0 && index < size) {
        array[index] = value;
    }
}

// Obtenir un élément d'un tableau int16
inline int16_t esp_nn_get_element_s16(const int16_t *array, int32_t index) {
    return array[index];
}

#endif // ESP_NN_WRAPPER_H
