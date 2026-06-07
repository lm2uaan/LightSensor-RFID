#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>

// Định nghĩa chân GPIO cho giao tiếp I2C của BH1750
#define BH1750_SDA 18
#define BH1750_SCL 17

// Khai báo các hàm toàn cục để main.cpp có thể gọi được
void bh1750_Init();
float bh1750_ReadLux();

#endif
