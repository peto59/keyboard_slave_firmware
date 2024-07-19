#include "slave.h"
#include "common.h"

#define ROWS 2
#define COLS 2
uint_fast8_t matrix[ROWS];

uint_fast8_t col_pins [COLS] = {14, 17};
uint_fast8_t row_pins [ROWS] = {15, 16};

int main(){
    run_slave(SLAVE_I2C_ADDRESS_RIGHT, matrix, col_pins, row_pins, COLS, ROWS);
    return 0;
}