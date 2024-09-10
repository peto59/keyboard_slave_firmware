#ifndef SLAVE_H_INCLUDED
#define SLAVE_H_INCLUDED

#include "pico/stdlib.h"

#define DEBUG true

#define I2C_TIMEOUT_US 100000
#define I2C_BUS_SPEED 1000000

#define I2C_SLAVE_SDA_PIN 4U
#define I2C_SLAVE_SCL_PIN 5U

void run_slave(uint8_t i2c_slave_address, uint_fast8_t* matrix_local, uint_fast8_t* col_pins_local, uint_fast8_t* row_pins_local, uint_fast8_t cols_local, uint_fast8_t rows_local);

#endif // SLAVE_H_INCLUDED
