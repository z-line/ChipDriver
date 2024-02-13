#ifndef __I2C_SOFT_H
#define __I2C_SOFT_H

#include "stdbool.h"
#include "stdint.h"

typedef void (*set_i2c_scl)(bool high);
typedef void (*set_i2c_sda)(bool high);
typedef bool (*get_i2c_scl)(void);
typedef bool (*get_i2c_sda)(void);
typedef void (*i2c_soft_delay_us)(uint32_t us);

typedef struct {
  set_i2c_scl m_set_scl;
  set_i2c_sda m_set_sda;
  get_i2c_scl m_get_scl;
  get_i2c_sda m_get_sda;
  i2c_soft_delay_us m_delay_us;
} i2c_soft_context_t;

bool i2c_soft_init(i2c_soft_context_t* context, set_i2c_scl set_scl,
                   set_i2c_sda set_sda, get_i2c_scl get_scl,
                   get_i2c_sda get_sda, i2c_soft_delay_us delay_us);
void i2c_soft_start(i2c_soft_context_t* context);
void i2c_soft_stop(i2c_soft_context_t* context);
void i2c_soft_ack(i2c_soft_context_t* context);
void i2c_soft_nack(i2c_soft_context_t* context);
bool i2c_soft_wait_ack(i2c_soft_context_t* context);
void i2c_soft_write(i2c_soft_context_t* context, uint8_t byte);
uint8_t i2c_soft_read(i2c_soft_context_t* context);

#endif
