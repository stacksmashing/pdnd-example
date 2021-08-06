cmake_minimum_required(VERSION 3.13)
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
project(pdnd_example)
 
pico_sdk_init()

add_executable(pdnd_example)

pico_generate_pio_header(pdnd_example ${CMAKE_CURRENT_LIST_DIR}/pdnd/pio/spi.pio)
pico_generate_pio_header(pdnd_example ${CMAKE_CURRENT_LIST_DIR}/pdnd/pio/i2c.pio)
pico_generate_pio_header(pdnd_example ${CMAKE_CURRENT_LIST_DIR}/pdnd/pio/uart_rx.pio)
pico_generate_pio_header(pdnd_example ${CMAKE_CURRENT_LIST_DIR}/pdnd/pio/uart_tx.pio)

target_sources(pdnd_example PRIVATE
        main.c

        # PIO components
        pdnd/pio/pio_spi.c
        pdnd/pio/pio_i2c.c

        # PDND source
        pdnd/pdnd.c
        pdnd/pdnd_spi.c
        
        # Display support
        pdnd/pdnd_display.c
        pdnd/display/FreeSans5pt7b.c
        pdnd/display/FreeSans9pt7b.c
        pdnd/display/font_renderer.c
        pdnd/display/ssd1306.c
        hello.c
        )

target_link_libraries(pdnd_example PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pdnd_example)

# enable usb output, disable uart output
pico_enable_stdio_usb(pdnd_example 1)
pico_enable_stdio_uart(pdnd_example 0)
