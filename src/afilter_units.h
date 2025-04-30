#ifndef AFILTER_UNITS_H
#define AFILTER_UNITS_H

#include <stddef.h>
#include <stdlib.h>

// 滤波器类型定义
typedef enum {
    FILTER_TYPE_MEAN,        // 均值滤波
    FILTER_TYPE_MEDIAN,      // 中值滤波
    FILTER_TYPE_EXPONENTIAL  // 指数滤波
} FilterType;

// 数据类型定义
typedef enum {
    DATA_TYPE_INT,    // 整数类型
    DATA_TYPE_FLOAT,  // 浮点数类型
    DATA_TYPE_DOUBLE  // 双精度浮点数类型
} DataType;

// 通用滤波器接口
typedef struct {
    FilterType filter_type;  // 滤波器类型
    DataType data_type;      // 数据类型
    void *filter_instance;   // 指向具体滤波器实例的指针
} GenericFilter;

#endif // AFILTER_UNITS_H
