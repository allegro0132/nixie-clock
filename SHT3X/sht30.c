#include "ioi2c.h"
#include "data_type.h"
#include "sht_crc8.h"
#include "bsp.h"
#include "platform.h"

bool_t sht30_get_value(f32_t *temp_value,f32_t *humi_value)
{
  u8_t cammand0[2] = {0x24,0x16};
  u8_t i=0,value[6] = {0};
  f32_t temp0 = 0,temp1 = 0,humi0 = 0,humi1 = 0;
  for(i=0;i<6;i++)
  {
    value[i] = 0;
  }
  i2c_write_bytes(0x88,cammand0,2);
  {
    bsp_delay_ms(10);
    i2c_read_bytes(0x88,value,6);
  }

  if((value[2] != sht_crc8(value,2)))
  {
    return false;
  }
  if((value[5] != sht_crc8((value+3),2)))
  {
    return false;
  }
  {
    temp0 = ((u16_t)value[0]<<8) + value[1];
    humi0 = ((u16_t)value[3]<<8) + value[4];
    humi1 = 100*(humi0/(65535));
    temp1 = 175*(temp0/65535)-45;
    
    if(humi1>=100)
      humi1 = 99.9; 
  }
    *temp_value = temp1;
    *humi_value = humi1;

  return true;
}