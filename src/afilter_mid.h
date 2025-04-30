#ifndef AFILTER_MID_H
#define AFILTER_MID_H

#include "afilter_units.h" // 包含公用函数定义等内容
#include <stddef.h>
#include <stdlib.h>

// 滤波器结构体
typedef struct {
    size_t window_size;          // 滤波窗口大小
    size_t buffer_index;         // 当前缓冲区索引
    void *buffer;                // 数据缓冲区（通用指针）
    void *(*update)(void *self, void *input); // 函数指针，用于更新滤波器
} MeanFilter;

// 静态宏创建均值滤波器
#define MEAN_FILTER_STATIC_CREATE(name, type, size) \
    type name##_buffer[size] = {0};                 \
    MeanFilter name = {                             \
        .window_size = size,                        \
        .buffer_index = 0,                          \
        .buffer = name##_buffer,                    \
        .update = mean_filter_##type##_update       \
    }

// 动态创建句柄和缓冲区
MeanFilter *mean_filter_create_dynamic(size_t window_size, size_t element_size, void *(*update_func)(void *self, void *input));

// 动态创建句柄，使用外部提供的静态缓冲区
MeanFilter *mean_filter_create_static_buffer(size_t window_size, void *buffer, void *(*update_func)(void *self, void *input));

// 静态创建句柄和缓冲区
MeanFilter *mean_filter_create_static(MeanFilter *filter, size_t window_size, void *buffer, void *(*update_func)(void *self, void *input));

// 销毁动态创建的均值滤波器
void mean_filter_destroy(MeanFilter *filter);

// 更新均值滤波器
void *mean_filter_update(MeanFilter *filter, void *input);

// 不同数据类型的更新函数
void *mean_filter_int_update(void *self, void *input);
void *mean_filter_float_update(void *self, void *input);

#endif // AFILTER_MID_H