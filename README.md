# RPI-Pico-I2C
This project is for an I2C MPU6050 Sensor with RPI Pico in C++. This uses I2C protocol to read and write to a temperature sensor and helps with software toolchain development with RPI software. 

## Description
This project contains a C++ program using the include "hardware/i2c.h" to use definitions, functions, and macros for I2C. I set up the MPU6050 bus address and created a function to reset the MPU6050. From there I made a function to read and store the data for the acceleration, gyroscope, and temperature. This involved getting the address of the acceleration, gyroscope, and temperature then using the I2C to read and write the data using registers and combining the two to read the raw data. From there I set up the SDA and SCL to the I2C and set the pins to pull up. Finally, I stored the data and printed it to the terminal.

## Demo Video
https://www.youtube.com/watch?v=mC2COQogiJc

## Dependencies
## Hardware
* https://www.raspberrypi.com/products/raspberry-pi-pico/

### Software
* Wokwi Simulation
* https://github.com/raspberrypi/pico-sdk

### Author
* Steven Hernandez
  - www.linkedin.com/in/steven-hernandez-a55a11300
  - https://github.com/stevenhernandezz
