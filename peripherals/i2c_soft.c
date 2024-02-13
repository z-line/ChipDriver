#include "i2c_soft.h"

#include "stddef.h"

bool i2c_soft_init(i2c_soft_context_t* context, set_i2c_scl set_scl,
                   set_i2c_sda set_sda, get_i2c_scl get_scl,
                   get_i2c_sda get_sda, i2c_soft_delay_us delay_us) {
  if (set_scl == NULL || set_sda == NULL || get_scl == NULL ||
      get_sda == NULL || delay_us == NULL) {
    return false;
  }
  context->m_set_scl = set_scl;
  context->m_get_scl = get_scl;
  context->m_set_sda = set_sda;
  context->m_get_sda = get_sda;
  context->m_delay_us = delay_us;
  return true;
}

void i2c_soft_start(i2c_soft_context_t* context) {
  context->m_set_scl(true);
  context->m_set_sda(true);
  context->m_delay_us(5);
  context->m_set_sda(false);
  context->m_delay_us(5);
  context->m_set_scl(false);
}

void i2c_soft_stop(i2c_soft_context_t* context) {
  context->m_set_scl(false);
  context->m_set_sda(false);
  context->m_delay_us(2);
  context->m_set_scl(true);
  context->m_delay_us(5);
  context->m_set_sda(true);
  context->m_delay_us(5);
}

void i2c_soft_ack(i2c_soft_context_t* context) {
  context->m_set_scl(false);
  context->m_set_sda(false);
  context->m_delay_us(5);
  context->m_set_scl(true);
  context->m_delay_us(5);
  context->m_set_scl(false);
}

void i2c_soft_nack(i2c_soft_context_t* context) {
  context->m_set_scl(false);
  context->m_set_sda(true);
  context->m_delay_us(2);
  context->m_set_scl(true);
  context->m_delay_us(5);
  context->m_set_scl(false);
}

bool i2c_soft_wait_ack(i2c_soft_context_t* context) {
  context->m_set_scl(false);
  context->m_set_sda(true);
  context->m_delay_us(2);
  context->m_set_scl(true);
  context->m_delay_us(2);
  if (context->m_get_sda()) {
    i2c_soft_stop(context);
    return true;
  } else {
    context->m_set_scl(false);
    return false;
  }
}

void i2c_soft_write(i2c_soft_context_t* context, uint8_t byte) {
  context->m_set_scl(false);
  for (uint8_t i = 0; i < 8; i++) {
    if (byte & 0x80) {
      context->m_set_sda(true);
    } else {
      context->m_set_sda(false);
    }
    byte <<= 1;
    context->m_delay_us(2);
    context->m_set_scl(true);
    context->m_delay_us(2);
    context->m_set_scl(false);
  }
}

uint8_t i2c_soft_read(i2c_soft_context_t* context) {
  uint8_t byte = 0;
  for (uint8_t i = 0; i < 8; i++) {
    context->m_set_scl(false);
    context->m_delay_us(2);
    context->m_set_scl(true);
    context->m_set_sda(true);
    byte = (byte << 1) | context->m_get_sda();
  }
  return byte;
}
