#ifndef __CH442_H
#define __CH442_H

#include "stdbool.h"
#include "stdint.h"

typedef enum {
  OUT_RAM_1,
  OUT_RAM_2,
  OUT_RAM_3,
  OUT_RAM_4,
} out_ram_index_e;

typedef union {
  struct {
    uint8_t io0 : 1;
    uint8_t io1 : 1;
    uint8_t io2 : 1;
    uint8_t io3 : 1;
    uint8_t io4 : 1;
    uint8_t io5 : 1;
    uint8_t io6 : 1;
    uint8_t io7 : 1;
  } __attribute__((__packed__));
  uint8_t value;
} __attribute__((__packed__)) io_t;

typedef union {
  struct {
    uint8_t o0 : 1;
    uint8_t o1 : 1;
    uint8_t o2 : 1;
    uint8_t o3 : 1;
    uint8_t : 4;
  } __attribute__((__packed__));
  uint8_t value;
} __attribute__((__packed__)) out_t;

typedef void (*i2c_read)(uint8_t in, uint8_t* out, uint8_t len);
typedef void (*i2c_write)(uint8_t* data, uint8_t len);

typedef struct {
  i2c_read i2c_read_handle;
  i2c_write i2c_write_handle;
} ch442_context_t;

bool init_io_extender(ch442_context_t* context, i2c_read read, i2c_write write);
void set_io(ch442_context_t* context, out_ram_index_e index, io_t io);
io_t get_io(ch442_context_t* context);
void set_out(ch442_context_t* context, out_t out);

#endif
