# Description

The **DIM** board is an RS485 to UART/USB interface, which can be used as a debug board to monitor RS485 frames sent within a DINFox system. It embeds the with the following features:

* Optional RS485 bus **power** supply.
* USB and RS485 bus voltage **measurements**.
* Dynamic **addressed or direct** mode.
* RS485 **nodes scanning**.

# Hardware

The boards were designed on **Circuit Maker V2.0**. Below is the list of hardware revisions:

| Hardware revision | Description | Status |
|:---:|:---:|:---:|
| [DIM HW1.0](https://365.altium.com/files/3F3B832D-FFF6-457E-A74F-EDA6BAF90587) | Initial version. | :x: |
| [DIM HW1.1](https://365.altium.com/files/D0E36E2E-D212-4D50-BA3B-173AD1895161) | Add transistor on VRS voltage measurement to save energy consumption.<br>Add jumper on RS485 bus power supply. | :white_check_mark: |

# Embedded software

## Environment

The embedded software is developed under **Eclipse IDE** version 2023-09 (4.29.0) and **GNU MCU** plugin. The `script` folder contains Eclipse run/debug configuration files and **JLink** scripts to flash the MCU.

## Target

The boards are based on the **STM32L011F4P3** microcontroller of the STMicroelectronics L0 family. Each hardware revision has a corresponding **build configuration** in the Eclipse project, which sets up the code for the selected board version.

## Structure

The project is organized as follow:

* `inc` and `src`: **source code** split in 6 layers:
    * `registers`: MCU **registers** adress definition.
    * `peripherals`: internal MCU **peripherals** drivers.
    * `utils`: **utility** functions.
    * `components`: external **components** drivers.
    * `nodes`: **Node interfaces** layer.
    * `applicative`: high-level **application** layers.
* `startup`: MCU **startup** code (from ARM).
* `linker`: MCU **linker** script (from ARM).

## Dependencies

The `inc/dinfox` and `src/dinfox` folders of the [XM project](https://github.com/Ludovic-Lesur/xm) must linked to the DIM project, as they contain common data definition related to the DINFox system.
