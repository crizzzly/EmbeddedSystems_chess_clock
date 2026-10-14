# Chess Clock — Embedded Systems Project

A microcontroller-based chess clock developed in C for the Microchip dsPIC33 platform. The project explores low-level embedded programming, peripheral control and time-critical software.

## Project Overview

This project was developed as part of a five-person university group project. My primary responsibility was the software implementation.

The firmware implements a chess clock with configurable time controls, a menu interface and hardware interaction through an LCD and a rotary encoder.

## Features

- Chess clock with configurable time limits
- Move-limit and speed-chess modes
- Menu navigation using a rotary encoder
- LCD-based user interface
- Timer- and interrupt-based timing
- Direct microcontroller register access
- Piezo buzzer output and sound sequences

## Hardware

- **Microcontroller:** Microchip dsPIC33EP512MU810
- **Board:** EDA dsPIC33 experiment board
- **Display:** LCD
- **Input:** Rotary encoder
- **Audio:** Piezo buzzer

The project was designed for the dsPIC33 board. Compatibility with the PIC24H variant was mentioned in the original project documentation but has not been verified.

## Technology Stack

- **Language:** C
- **Platform:** Microchip dsPIC33
- **Toolchain:** MPLAB X IDE / XC16
- **Build system:** Makefiles
- **Documentation:** Doxygen

## My Contribution

This was a five-person university group project. I was primarily responsible for the software implementation, including:

- Implementing the embedded application logic
- Working with microcontroller registers and peripheral control
- Implementing timing and interrupt-driven functionality
- Integrating the LCD, rotary encoder and buzzer
- Debugging and testing firmware behaviour

## Project Status

This repository preserves the project as a university project. The source code and build configuration are provided for inspection; the current build status on a clean environment has not yet been verified.

## Building

The project uses the Microchip XC16 toolchain and MPLAB X project files.

A compatible XC16 installation and the required target-device support are needed to build the firmware. Local toolchain paths may need to be configured for your environment.

## Documentation

API and source documentation is generated with Doxygen. See the `Doxyfile` and the `docs/` directory.

## Known Limitations

- Compatibility with the PIC24H hardware variant has not been tested.
- Countdown behaviour at or below zero should be reviewed and tested.

## Project Context

Developed as part of a university embedded-systems course at Hochschule Aalen.

## License

See the repository for licensing information.