#include "Handle_RFID.h"

// Khởi tạo đối tượng RFID truyền vào chân CS và RST
MFRC522 mfrc522(RFID_CS_PIN, RFID_RST_PIN);

void rfid_Init() {
    // Khởi tạo giao tiếp SPI cho RFID với các chân Custom
    SPI.begin(RFID_SCK_PIN, RFID_MISO_PIN, RFID_MOSI_PIN, RFID_CS_PIN);
    
    // Khởi động module RC522
    mfrc522.PCD_Init();
    
    Serial.println("✅ [RFID] Khoi tao thanh cong, dang cho quet the...");
}

String rfid_GetUID() {
    // 1. Kiểm tra xem có thẻ mới đưa vào vùng từ trường không
    // Nếu không có, lập tức thoát hàm (return "") để ESP32 làm việc khác (chạy màn hình, blynk...)
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return ""; 
    }

    // 2. Kiểm tra xem có đọc được dữ liệu thẻ không
    if (!mfrc522.PICC_ReadCardSerial()) {
        return "";
    }

    // 3. Có thẻ -> Xử lý đọc dải ID (UID)
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        // Thuật toán bù số "0": Nếu giá trị byte < 16 (0x10), thêm " 0" để tránh bị lỗi mất số
        // Ví dụ: 0x06 sẽ thành " 06" thay vì " 6"
        uidString += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    
    // 4. Chuẩn hóa chuỗi dữ liệu
    uidString.toUpperCase(); // Viết hoa toàn bộ chữ cái (ví dụ a b c -> A B C)
    uidString.trim();        // Cắt bỏ khoảng trắng bị dư ở đầu chuỗi
    
    // 5. Lệnh bắt buộc: Đánh thuốc mê (Halt) thẻ ngay sau khi đọc xong
    // Giúp thẻ không bị đọc lặp đi lặp lại liên tục gây loạn Servo
    mfrc522.PICC_HaltA();    

    return uidString; // Gửi chuỗi ID cuối cùng (VD: "91 D9 F2 06") về cho main.cpp
}
