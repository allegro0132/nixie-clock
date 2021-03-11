/**
 * @file ioi2c.c
 *
 * @copyright This file creat by rensuiyi ,all right reserve!
 * 
 * @author rensuyi
 * 
 * @date 2014/1/2 14:52:13
 */
#include "ioi2c.h"
#include "data_type.h"

#define SCL_OUT()            
#define GET_SDA()            

#define SDA_L()              
#define SDA_H()              
#define SCL_L()              
#define SCL_H()              

#define SDA_OUT()            
#define SDA_IN()             

#define i2c_delay()          
#define i2c_delay2()         


#define  __ioi2c_debug(x,y...)   


static void i2c_start() {
    SDA_OUT();
    SCL_OUT();
    i2c_delay();
    SDA_H();
    SCL_H();
    i2c_delay();
   
    SDA_L();    
    i2c_delay();
    SCL_L();
}

static void i2c_stop() {

    SDA_OUT();

    SDA_L();
    i2c_delay();
    SCL_H();
    i2c_delay();
    SDA_H();
    i2c_delay2();
}

static bool_t i2c_waitack() {
    bool_t ack;

    SDA_IN();
    i2c_delay();
    SCL_H();
    i2c_delay();
    ack = !GET_SDA();    /* ACK : SDA pin is pulled low */
    //__ioi2c_debug("%s\n", ack ? "ACK" : "NACK");
    SCL_L();
    i2c_delay();
    return ack;
}

bool_t i2c_writeb(u8_t data) {
    s8_t i;
    bool_t bit;

    SDA_OUT();
    for (i = 7; i >= 0; i--) {
        SCL_L();
        bit = (data >> i) & 1;
        if(bit){SDA_H();}else{ SDA_L();}
        i2c_delay();
        SCL_H();
        i2c_delay();
    }
    SCL_L();
    i2c_delay();
    return i2c_waitack();
}

static bool_t i2c_readb(u8_t *out) {
    u8_t i;
    u8_t data = 0;

    SDA_IN(); 
    SDA_H();
    i2c_delay();
    for (i = 0; i < 8; i++) {
        data <<= 1;
        SCL_H();
        i2c_delay();
        if (GET_SDA()) data |= 1;
        SCL_L();
        i2c_delay2();
    }
    *out = data;
    return true;
}

static bool_t i2c_send_ack_or_nack( bool_t ack) {
    SDA_OUT();
    if (ack) SDA_L();
    i2c_delay();
    SCL_H();
    i2c_delay();
    SCL_L();
    return true;
}

static bool_t i2c_send_address(u8_t addr,
                        u8_t retries) {
    bool_t ret = 0;
	
    i2c_start();
    ret = i2c_writeb(addr);

    return ret;
}

bool_t i2c_read_bytes(u8_t address, u8_t *buf, u16_t len) {
    if (true != i2c_send_address( address | 0x01, 2)) {
        __ioi2c_debug("Send i2c address failed\r\n");
        goto err_out;
    }
    while (len > 0) {
        len--;
        if (true != i2c_readb(buf++)) {
            __ioi2c_debug("read data %d failed\r\n", len);
            goto err_out;
        }
        i2c_send_ack_or_nack(len != 0);
    }
    i2c_stop();
    return true;
err_out:
    i2c_stop();
    return false;
}


bool_t i2c_write_bytes(u16_t address, u8_t *buf, u16_t len) {
    if (true != i2c_send_address( address & 0xFE, 2)) {
        __ioi2c_debug("Send i2c address failed\r\n");
        goto err_out;
    }
    while (len > 0) {
        len--;
        if (true != i2c_writeb( *buf++)) {
            __ioi2c_debug("write data %d failed\r\n", len);
            goto err_out;
        }
    }
    i2c_stop();
    return true;
err_out:
    i2c_stop();
    return false;
}


bool_t i2c_write_offset( u16_t address, u8_t *buf, u16_t len) {
    if (true != i2c_send_address(address & 0xFE, 2)) {
        __ioi2c_debug("Send i2c address failed\r\n");
        goto err_out;
    }
    while (len > 0) {
        len--;
        if (true != i2c_writeb(*buf++)) {
            __ioi2c_debug("write data %d failed\r\n", len);
            goto err_out;
        }
    }
    i2c_delay();
    SCL_H();
    //i2c_stop();
    return true;
err_out:
    i2c_stop();
    return false;
}

