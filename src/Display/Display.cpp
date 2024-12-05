#include <Arduino.h>
#include "Display.h"

// 使用 U8g2 库初始化 OLED 显示屏，I2C 地址为 0x3C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

uint64_t fullChipId;  // 存储完整的 64 位 MAC 地址
uint32_t shortChipId; // 存储低 24 位短 ID
// 初始化显示
void Display::init()
{
    u8g2.begin();
    u8g2.enableUTF8Print(); // 启用 UTF-8 支持
}

// 显示初始化完成
void Display::showInitializationComplete()
{
    // 获取完整的 64 位 eFuse MAC 地址
    fullChipId = ESP.getEfuseMac();
    // 提取低 24 位（短 ID）
    shortChipId = (uint32_t)(fullChipId & 0xFFFFFF);
    
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);

    u8g2.setCursor(10, 20);
    u8g2.print("Start Done!");
    u8g2.setCursor(10, 35);
    u8g2.print("ID:");
    u8g2.printf("%06X", shortChipId); // 使用 printf 格式化输出 shortChipId

    // 将光标移动到下一行显示完整的 MAC 地址
    u8g2.setCursor(10, 45);
    u8g2.print("MAC:");
    u8g2.printf("%08X%08X", (uint32_t)(fullChipId >> 32), (uint32_t)fullChipId); // 使用 printf 格式化输出 fullChipId(fullChipId >> 32), (uint32_t)fullChipId);
    u8g2.drawDisc(110, 10, 5, U8G2_DRAW_ALL);
    u8g2.sendBuffer();
}

//
void Display::showDistance(bool isLocked, float distance)
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf); // Set a smaller font for better spacing

    u8g2.setCursor(10, 5); // First line for ID
    u8g2.print("ID: ");
    u8g2.printf("%06X", shortChipId);

    u8g2.setCursor(10, 20); // Second line for time
    u8g2.print("Time: ");
    u8g2.print(millis() / 1000);

    u8g2.setCursor(10, 35); // Third line for status
    u8g2.print("Status: ");
    u8g2.print(isLocked ? "Lock" : "Unlock");

    u8g2.setCursor(10, 50); // Fourth line for distance
    u8g2.print("Distance: ");
    u8g2.print(distance, 2);
    u8g2.print(" cm");

    u8g2.sendBuffer();
}

void Display::showMessage(const char *message)
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setCursor(10, 20);
    u8g2.print(message);
    u8g2.sendBuffer();
}