# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Protocolos_comunicacao C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1


file(GLOB INCLUDES_FILES "includes/**/*.h")
file(GLOB SOURCES_FILES "src/**/*.c")
add_executable(Protocolos_comunicacao main.c
    ${INCLUDES_FILES}
    ${SOURCES_FILES}
)

pico_generate_pio_header(Protocolos_comunicacao ${CMAKE_CURRENT_LIST_DIR}/src/utils/ws2812.pio)

pico_set_program_name(Protocolos_comunicacao "Protocolos_comunicacao")
pico_set_program_version(Protocolos_comunicacao "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Protocolos_comunicacao 0)
pico_enable_stdio_usb(Protocolos_comunicacao 1)

# Add the standard library to the build
target_link_libraries(Protocolos_comunicacao
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Protocolos_comunicacao PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/includes/utils
    ${CMAKE_CURRENT_LIST_DIR}/includes/src
)

# Add any user requested libraries
target_link_libraries(Protocolos_comunicacao 
        hardware_i2c
        hardware_pio
        hardware_uart
        )

pico_add_extra_outputs(Protocolos_comunicacao)

