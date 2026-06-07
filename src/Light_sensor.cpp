#include "Light_sensor.h"
#include <Wire.h>
#include <BH1750.h>

// Khởi tạo đối tượng cảm biến ánh sáng
BH1750 lightMeter;

void bh1750_Init() {
    // Ép vi điều khiển ESP32-S3 mở chuẩn I2C ở đúng 2 chân SDA và SCL đã chọn
    Wire.begin(BH1750_SDA, BH1750_SCL); 

    // Bật cảm biến ở chế độ đọc liên tục, độ phân giải cao nhất (1 Lux)
    // Chế độ này giúp lọc nhiễu quang học rất tốt
    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
        Serial.println("✅ [BH1750] Khoi tao cam bien anh sang THANH CONG!");
    } else {
        Serial.println("❌ [BH1750] LOI: Khong the ket noi. Kiem tra lai day I2C!");
    }
}

float bh1750_ReadLux() {
    // Đọc và trả về giá trị cường độ ánh sáng (Lux) trực tiếp cho main.cpp
    return lightMeter.readLightLevel();
}
