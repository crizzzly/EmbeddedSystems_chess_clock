cmake_minimum_required(VERSION 3.10)
project(chess_clock C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.c
    src/app/audio/melodies.c
    src/drivers/digitalIO.c
    src/drivers/lcd.c
    src/drivers/onboardBtn.c
    src/drivers/onboardLeds.c
    src/drivers/quadratureEncoder.c
    src/drivers/timer.c
    src/system/system.c
    src/utils/hexdec.c
    src/utils/time.c
)

# Header files (for IDE indexing)
set(HEADERS
    src/app/app_data.h
    src/app/audio/melodies.h
    src/app/audio/music.h
    src/app/player_data.h
    src/drivers/digitalIO.h
    src/drivers/lcd.h
    src/drivers/onboardBtn.h
    src/drivers/onboardLeds.h
    src/drivers/print_lcd.h
    src/drivers/quadratureEncoder.h
    src/drivers/timer.h
    src/system/config_bits.h
    src/utils/time.h
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/app
    ${CMAKE_SOURCE_DIR}/src/app/audio
    ${CMAKE_SOURCE_DIR}/src/drivers
    ${CMAKE_SOURCE_DIR}/src/system
    ${CMAKE_SOURCE_DIR}/src/utils
    /opt/microchip/xc16/v2.10/include
    /opt/microchip/xc16/v2.10/support/generic/h
    /opt/microchip/xc16/v2.10/support/generic
)

# Create executable (for IDE indexing only)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Cross-compilation settings for dsPIC33EP512MU810
# Adjust these paths according to your XC16 installation
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR "dsPIC33EP512MU810")

# XC16 toolchain settings
set(CMAKE_C_COMPILER "/opt/microchip/xc16/v2.10/bin/xc16-gcc")
set(CMAKE_C_FLAGS "-mcpu=33EP512MU810 -O2 -msmall-data")

# Compiler definitions
add_definitions(-D__dsPIC33EP512MU810__)
