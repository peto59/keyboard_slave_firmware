cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
include_directories(${PICO_SDK_DIR}/include)

project(pico_test_sdk)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()
set (pico_bare_metal 1)

add_library(slave_lib STATIC slave.c)
target_link_libraries(
    slave_lib
    pico_stdlib
    pico_i2c_slave
    hardware_i2c
    pico_multicore
)

add_executable(
    main
    main.c
)

add_executable(
    slave_left
    slave_left.c
)

add_executable(
    slave_right
    slave_right.c
)

target_link_libraries(
    main 
    pico_stdlib 
    pico_i2c_slave
    hardware_i2c
)

target_link_libraries(
    slave_left 
    slave_lib
)

target_link_libraries(
    slave_right 
    slave_lib
)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

pico_add_extra_outputs(main)
pico_add_extra_outputs(slave_left)
pico_add_extra_outputs(slave_right)