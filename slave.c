#include "slave.h"
#include "pico/multicore.h"
#include "common.h"
#include <stdio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include "hardware/gpio.h"

static uint_fast8_t rows;
static uint_fast8_t cols;

static uint_fast8_t read_row = 0;
static uint_fast8_t* matrix;
static uint_fast8_t* col_pins;
static uint_fast8_t* row_pins;

static void i2c1_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
    case I2C_SLAVE_REQUEST: // master is requesting data
        read_row = i2c_read_byte_raw(i2c);
        #if DEBUG == true
            gpio_put(18, 1);
        #endif
        if(read_row < rows){
            i2c_write_byte_raw(i2c, matrix[read_row]);
        }else{
            i2c_write_byte_raw(i2c, 0);
        }
        break;
    default:
        break;
    }
}

void matrix_scan() {
    uint_fast8_t r, c;
    while (true) {
        for (c = 0; c < cols; c++){
            gpio_put(col_pins[c], 1); // Set column high
            sleep_us(1);
            for (r = 0; r < rows; r++){
                if(gpio_get(row_pins[r])){
                    matrix[r] |= (1 << c);
                }else{
                    matrix[r] &= ~(1 << c);
                }
            }
            gpio_put(col_pins[c], 0); // Set column low
        }
    }
}

void run_slave(uint8_t i2c_slave_address, uint_fast8_t* matrix_local, uint_fast8_t* col_pins_local, uint_fast8_t* row_pins_local, uint_fast8_t cols_local, uint_fast8_t rows_local) {
    stdio_init_all();

    matrix = matrix_local;
    col_pins = col_pins_local;
    row_pins = row_pins_local;
    cols = cols_local;
    rows = rows_local;

    for (int i = 0; i < rows; i++) {
        matrix[i] = 0;
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_IN);
        gpio_pull_down(row_pins[i]);
    }

    for (int i = 0; i < cols; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_OUT);
    }

#if DEBUG == true
    gpio_init(18);
    gpio_set_dir(18, GPIO_OUT);
#endif

    multicore_launch_core1(matrix_scan);


    gpio_init(I2C_SLAVE_SDA_PIN);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);

    gpio_init(I2C_SLAVE_SCL_PIN);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);

    i2c_init(i2c1, I2C_BUS_SPEED);
    i2c_slave_init(i2c1, i2c_slave_address, &i2c1_slave_handler);

    while (true) {
        tight_loop_contents();
    }
}