#include "ch422.h"

#include "stddef.h"

typedef union {
  struct {
    uint8_t io_oe : 1;
    uint8_t : 1;
    uint8_t a_scan : 1;
    uint8_t : 1;
    uint8_t od_en : 1;
    uint8_t : 2;
    uint8_t sleep : 1;
  } __attribute__((__packed__));
  uint8_t value;
} __attribute__((__packed__)) sys_config_t;

typedef enum {
  SET_CONFIG = 0x48,
  SET_OUT = 0x46,
  SET_IO_1 = 0x70,
  SET_IO_2 = 0x72,
  SET_IO_3 = 0x74,
  SET_IO_4 = 0x76,
  GET_IO = 0x4D
} cmd_t;

static const char* TAG = "CH422";

static void ch442_write(ch442_context_t* context, cmd_t cmd, uint8_t data);
static uint8_t ch442_read(ch442_context_t* context, cmd_t cmd);

bool init_io_extender(ch442_context_t* context, i2c_read read,
                      i2c_write write) {
  if (read == NULL || write == NULL) {
    return false;
  }
  context->i2c_read_handle = read;
  context->i2c_write_handle = write;
  sys_config_t config = {.io_oe = 1, .a_scan = 0, .od_en = 0, .sleep = 0};
  ch442_write(context, SET_CONFIG, config.value);
  return true;
}

static void ch442_write(ch442_context_t* context, cmd_t cmd, uint8_t data) {
  uint8_t buf[] = {(uint8_t)cmd, data};
  context->i2c_write_handle(buf, sizeof(buf));
}

static uint8_t ch442_read(ch442_context_t* context, cmd_t cmd) {
  uint8_t ret = 0x0;
  uint8_t data = (uint8_t)cmd;
  context->i2c_read_handle(data, &ret, 1);
  return ret;
}

void set_io(ch442_context_t* context, out_ram_index_e index, io_t io) {
  cmd_t cmd;
  switch (index) {
    case OUT_RAM_1:
      cmd = SET_IO_1;
      break;
    case OUT_RAM_2:
      cmd = SET_IO_2;
      break;
    case OUT_RAM_3:
      cmd = SET_IO_3;
      break;
    case OUT_RAM_4:
      cmd = SET_IO_4;
      break;
    default:
      cmd = SET_IO_1;
      break;
  }
  ch442_write(context, cmd, io.value);
}

io_t get_io(ch442_context_t* context) {
  io_t io;
  io.value = ch442_read(context, GET_IO);
  return io;
}

void set_out(ch442_context_t* context, out_t out) {
  ch442_write(context, SET_OUT, out.value);
}
