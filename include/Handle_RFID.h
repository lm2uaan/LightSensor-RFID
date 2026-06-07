#ifndef HANDLE_RFID_H
#define HANDLE_RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Định nghĩa các chân cắm cho module RFID RC522 (Cắm vào cổng HD11 theo phần cứng)
#define RFID_CS_PIN    48
#define RFID_SCK_PIN   19
#define RFID_MOSI_PIN  35
#define RFID_MISO_PIN  20
#define RFID_RST_PIN   0

// Khai báo các hàm toàn cục để main.cpp có thể gọi được
void rfid_Init();
String rfid_GetUID();

#endif
