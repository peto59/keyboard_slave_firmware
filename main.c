#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include "common.h"
#include "slave.h"

static const uint I2C_MASTER_SDA_PIN = 2;
static const uint I2C_MASTER_SCL_PIN = 3;
//test delete later

int main() {
    stdio_init_all();

    gpio_init(I2C_SLAVE_SDA_PIN);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);

    gpio_init(I2C_SLAVE_SCL_PIN);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);

    uint br = i2c_init(i2c0, I2C_BUS_SPEED);
     
     for (size_t i = 0; i < 10; i++)
     {
        printf("I2C bus speed %u\n", br);
        sleep_ms(100);
     }
     

    while (true) {
        printf("-------------\n");
        for (uint8_t r = 0; r < 5; r++){
            int wr = i2c_write_timeout_us(i2c0, SLAVE_I2C_ADDRESS_RIGHT, &r, 1, false, 1000000);
            //printf("wr %i\n", wr);
            uint8_t read;
            int rd = i2c_read_timeout_us(i2c0, SLAVE_I2C_ADDRESS_RIGHT, &read, 1, false, 1000000);
            //printf("rd %i\n", rd);
            printf("%u\n", read);
            sleep_ms(100);
        }
        printf("-------------\n");
    }
}
