cmake_minimum_required(VERSION 3.13)
include(~/pico-sdk/pico_sdk_init.cmake)
project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_SDK_FETCH_FROM_GIT on)
pico_sdk_init()
include_directories(libs)
add_executable(main
example.c
led.c
led.h
RP2040_UART_Debugger/uart.c  # Include the UART source file
)

# Include the directory for UART headers
target_include_directories(main PRIVATE RP2040_UART_Debugger)

target_link_libraries(main pico_stdlib)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
