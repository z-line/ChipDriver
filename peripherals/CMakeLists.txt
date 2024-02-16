add_library(Peripherals OBJECT i2c_soft.c SerialPort.cpp)
target_include_directories(Peripherals PUBLIC .)