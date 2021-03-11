/**
 * @file bsp.h
 *
 * @copyright This file creat by chenyiheng
 * 
 * @author chenyiheng
 * 
 * @date 2016-10-12 15:36:27
 */
#ifndef __SHT30_H__
#define __SHT30_H__
#include "data_type.h"

   
extern bool_t sht30_get_value(f32_t *temp_value,f32_t *humi_value);

#endif