#include "slave.h"
#include "common.h"

#define ROWS 6
#define COLS 4
uint_fast8_t matrix[ROWS];

uint_fast8_t col_pins [COLS] = {15, 14, 13, 12};
uint_fast8_t row_pins [ROWS] = {19, 10, 9, 8, 7, 6};

int main(){
    run_slave(SLAVE_I2C_ADDRESS_LEFT, matrix, col_pins, row_pins, COLS, ROWS);
    return 0;
}
