#include "afilter_mid.h"
#include <string.h> // 用于 memset 和 memcpy

// 动态创建句柄和缓冲区
MeanFilter *mean_filter_create_dynamic(size_t window_size, size_t element_size, void *(*update_func)(void *self, void *input)) {
    // 分配滤波器结构体
    MeanFilter *filter = (MeanFilter *)malloc(sizeof(MeanFilter));
    if (!filter) {
        return NULL; // 分配失败
    }

    // 初始化滤波器
    filter->window_size = window_size;
    filter->buffer_index = 0;
    filter->update = update_func;

    // 分配缓冲区
    filter->buffer = malloc(window_size * element_size);
    if (!filter->buffer) {
        free(filter); // 如果缓冲区分配失败，释放滤波器结构体
        return NULL;
    }

    // 初始化缓冲区为 0
    memset(filter->buffer, 0, window_size * element_size);

    return filter;
}

// 动态创建句柄，使用外部提供的静态缓冲区
MeanFilter *mean_filter_create_static_buffer(size_t window_size, void *buffer, void *(*update_func)(void *self, void *input)) {
    if (!buffer) {
        return NULL; // 缓冲区不能为空
    }

    // 分配滤波器结构体
    MeanFilter *filter = (MeanFilter *)malloc(sizeof(MeanFilter));
    if (!filter) {
        return NULL; // 分配失败
    }

    // 初始化滤波器
    filter->window_size = window_size;
    filter->buffer_index = 0;
    filter->buffer = buffer; // 使用外部提供的缓冲区
    filter->update = update_func;

    return filter;
}

// 静态创建句柄和缓冲区
MeanFilter *mean_filter_create_static(MeanFilter *filter, size_t window_size, void *buffer, void *(*update_func)(void *self, void *input)) {
    if (!filter || !buffer) {
        return NULL; // 句柄或缓冲区不能为空
    }

    // 初始化滤波器
    filter->window_size = window_size;
    filter->buffer_index = 0;
    filter->buffer = buffer; // 使用外部提供的缓冲区
    filter->update = update_func;

    // 初始化缓冲区为 0
    memset(buffer, 0, window_size * sizeof(buffer[0]));

    return filter;
}

// 销毁动态创建的均值滤波器
void mean_filter_destroy(MeanFilter *filter) {
    if (filter) {
        if (filter->buffer) {
            free(filter->buffer); // 释放缓冲区（仅动态创建时）
        }
        free(filter); // 释放滤波器结构体
    }
}

// 更新均值滤波器
void *mean_filter_update(MeanFilter *filter, void *input) {
    if (!filter || !filter->update) {
        return NULL; // 无效滤波器或未设置更新函数
    }
    return filter->update(filter, input);
}

// 整数类型的更新函数
void *mean_filter_int_update(void *self, void *input) {
    MeanFilter *filter = (MeanFilter *)self;
    int *buffer = (int *)filter->buffer;
    int *value = (int *)input;

    // 替换缓冲区中的旧值
    int old_value = buffer[filter->buffer_index];
    buffer[filter->buffer_index] = *value;
    filter->buffer_index = (filter->buffer_index + 1) % filter->window_size;

    // 计算新的均值
    static int sum = 0;
    sum = sum - old_value + *value;
    static int result = 0;
    result = sum / (int)filter->window_size;

    return &result;
}

// 浮点数类型的更新函数
void *mean_filter_float_update(void *self, void *input) {
    MeanFilter *filter = (MeanFilter *)self;
    float *buffer = (float *)filter->buffer;
    float *value = (float *)input;

    // 替换缓冲区中的旧值
    float old_value = buffer[filter->buffer_index];
    buffer[filter->buffer_index] = *value;
    filter->buffer_index = (filter->buffer_index + 1) % filter->window_size;

    // 计算新的均值
    static float sum = 0.0f;
    sum = sum - old_value + *value;
    static float result = 0.0f;
    result = sum / (float)filter->window_size;

    return &result;
}
