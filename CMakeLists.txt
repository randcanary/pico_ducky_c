cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)
include(toolchain-rp2040.cmake)

# Project name
project(pico_ducky_c)

pico_sdk_init()

# Configuration projects
add_executable(pico_ducky_c
    src/main.c
    src/hooks.c
    src/usb_descriptors.c
    src/comm_external.c
    src/runner.c
)

target_include_directories(pico_ducky_c PRIVATE
    config/
    include/
    scripts/
)

target_link_libraries(pico_ducky_c PRIVATE
    pico_stdlib
    hardware_uart
    tinyusb_device
    tinyusb_board
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

target_compile_options(pico_ducky_c PRIVATE -Wall)

# enable usb output, disable uart output
pico_enable_stdio_usb(pico_ducky_c 1)
pico_enable_stdio_uart(pico_ducky_c 0)

# Run the entire project in SRAM
# pico_set_binary_type(pico_ducky_c copy_to_ram)

pico_add_extra_outputs(pico_ducky_c)