add_library(Peripherals OBJECT i2c_soft.c serial_port.cpp)
target_include_directories(Peripherals PUBLIC .)