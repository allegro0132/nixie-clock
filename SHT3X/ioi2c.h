/**
 * @file ioi2c.h
 *
 * @copyright This file creat by rensuiyi ,all right reserve!
 * 
 * @author rensuyi
 * 
 * @date 2014/1/2 14:52:45
 */
#ifndef __IOI2C_H__
#define __IOI2C_H__

#ifdef __cplusplus
extern "C" 
{
#endif /*__cplusplus */
#include "data_type.h"
 

  
extern bool_t i2c_read_bytes( u8_t address, u8_t *buf, u16_t len);
extern bool_t i2c_write_bytes(u16_t address, u8_t *buf, u16_t len);
extern bool_t i2c_write_offset( u16_t address, u8_t *buf, u16_t len);

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif /* __IOI2C_H__ */
