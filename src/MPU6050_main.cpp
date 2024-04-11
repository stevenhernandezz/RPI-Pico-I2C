#include <iostream>         
#include <cstdint>         
#include "pico/stdlib.h"    
#include "pico/binary_info.h" 
#include "hardware/i2c.h"   

// MPU6050 device bus address 0x68
static int addr = 0x68;

#ifdef i2c_default
// Function reset 
static void mpu6050_reset() {
  //resetting 
    uint8_t buf[] = {0x6B, 0x80}; 
    i2c_write_blocking(i2c_default, addr, buf, 2, false); 
}

// Function to read 
static void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
  //used to store 
    uint8_t buffer[6]; 

    // Reading acceleration reg 
    uint8_t val = 0x3B;  
    //writing the reg
    i2c_write_blocking(i2c_default, addr, &val, 1, true); 
    //reading the reg
    i2c_read_blocking(i2c_default, addr, buffer, 6, false); 
     //combining the two to print data
    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }
 
    // Reading gyroscope data
    val = 0x43; 
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 6, false); 
    //combining the two to print data
    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]); 
    }

    // Reading temperature data
    val = 0x41; 
    i2c_write_blocking(i2c_default, addr, &val, 1, true); 
    i2c_read_blocking(i2c_default, addr, buffer, 2, false); 
     //combining the two to print data
    *temp = buffer[0] << 8 | buffer[1]; 
}
#endif

int main() {
    stdio_init_all();

    // Checking I2C pins 
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/mpu6050_i2c example requires a board with I2C pins
    std::cout << "I2C pins were not defined" << std::endl; 
    return 0; 
#else
    std::cout << "Reading Data" << std::endl; 

    // I2C communication speed
    i2c_init(i2c_default, 400 * 1000); 
    //setting SDA to I2C
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C); 
    //setting SCL to I2C
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C); 
    //SDA pin
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN); 
    //SCL pin
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN); 

    // I2C pins for binary information
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    mpu6050_reset();

    // store data
    int16_t acceleration[3], gyro[3], temp;

    while (true) {
        // Reading data 
        mpu6050_read_raw(acceleration, gyro, &temp);
        std::cout << "Acc. X = " << acceleration[0] << ", Y = " << acceleration[1] << ", Z = " << acceleration[2] << std::endl;
        std::cout << "Gyro. X = " << gyro[0] << ", Y = " << gyro[1] << ", Z = " << gyro[2] << std::endl;
        std::cout << "Temp. = " << (temp / 340.0) + 36.53 << std::endl;
        sleep_ms(100);
    }
#endif
}
